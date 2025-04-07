// SPDX-FileCopyrightText: 2001 Bernd Gehrmann <bernd@kdevelop.org>
// SPDX-FileCopyrightText: 2004-2005 Sascha Cunz <sascha@kdevelop.org>
// SPDX-FileCopyrightText: 2007 Alexander Dymo <adymo@kdevelop.org>
// SPDX-FileCopyrightText: 2008 Anne-Marie Mahfouf <annma@kde.org>
// SPDX-FileCopyrightText: 2024 Carl Schwan <carl@carlschwan.eu>
//
// SPDX-License-Identifier: GPL-2.0-or-later

#include "generator.h"

#include "logging.h"
#include "prefs.h"

#include <KArchiveDirectory>
#include <KArchiveFile>
#include <KConfig>
#include <KConfigGroup>
#include <KLocalizedString>
#include <KMacroExpander>
#include <KTar>
#include <KZip>

#include <QDir>
#include <QFileInfo>
#include <QMimeDatabase>
#include <QRegularExpression>
#include <QStandardPaths>
#include <QTemporaryDir>

using namespace Qt::StringLiterals;

Generator::Generator(QObject *parent)
    : QObject(parent)
    , m_name(Prefs::appName())
    , m_location(Prefs::url())
    , m_authorName(Prefs::name())
    , m_authorEmail(Prefs::email())
    , m_version(Prefs::appVersion())
{
}

QString Generator::name() const
{
    return m_name;
}

QString Generator::location() const
{
    return m_location;
}

QString Generator::authorName() const
{
    return m_authorName;
}

QString Generator::authorEmail() const
{
    return m_authorEmail;
}

QString Generator::version() const
{
    return m_version;
}

void Generator::setName(const QString &name)
{
    if (m_name == name) {
        return;
    }
    m_name = name;
    Q_EMIT nameChanged();
}

void Generator::setLocation(const QString &location)
{
    if (m_location == location) {
        return;
    }
    m_location = location;
    Q_EMIT locationChanged();
}

void Generator::setAuthorName(const QString &authorName)
{
    if (m_authorName == authorName) {
        return;
    }
    m_authorName = authorName;
    Q_EMIT authorNameChanged();
}

void Generator::setAuthorEmail(const QString &authorEmail)
{
    if (m_authorEmail == authorEmail) {
        return;
    }
    m_authorEmail = authorEmail;
    Q_EMIT authorEmailChanged();
}

void Generator::setVersion(const QString &version)
{
    if (m_version == version) {
        return;
    }
    m_version = version;
    Q_EMIT versionChanged();
}

bool Generator::unpackArchive(const KArchiveDirectory *dir, const QString &dest, const QStringList &skipList, bool firstCall)
{
    bool failed = false;
    qCDebug(KAPPTEMPLATE) << "unpacking dir:" << dir->name() << "to" << dest;
    const QStringList entries = dir->entries();
    qCDebug(KAPPTEMPLATE) << "entries:" << entries.join(",");

    QTemporaryDir tdir;

    if (firstCall) {
        m_newFiles.clear();
    }

    // create path were we want copy files to
    if (!QDir::root().mkpath(dest)) {
        Q_EMIT errorOccurred(i18n("%1 cannot be created.", dest));
        return false;
    }

    int progress = 0;
    QMimeDatabase mimeDb;

    for (const QString &entry : entries) {
        progress++;
        Q_EMIT progressUpdated(int((progress / entries.size()) * 100));

        if (skipList.contains(entry)) {
            continue;
        }

        if (dir->entry(entry)->isDirectory()) {
            const KArchiveDirectory *file = dynamic_cast<const KArchiveDirectory *>(dir->entry(entry));
            QString newdest = dest + "/" + file->name();
            if (!QFileInfo(newdest).exists()) {
                if (!QDir::root().mkdir(newdest)) {
                    Q_EMIT errorOccurred(i18n("Path %1 could not be created.", newdest));
                    failed = true;
                    break;
                }
                m_newFiles.append(newdest);
            }
            if (!unpackArchive(file, newdest, skipList, false)) {
                failed = true;
                break;
            }
        } else if (dir->entry(entry)->isFile()) {
            const KArchiveFile *file = dynamic_cast<const KArchiveFile *>(dir->entry(entry));
            file->copyTo(tdir.path());
            QString destName = KMacroExpander::expandMacros(dest + '/' + file->name(), m_variables);
            if (QFile::exists(destName)) {
                Q_EMIT errorOccurred(
                    i18n("Could not copy template file to %1, because the file is "
                         "already exists. The project has not been generated and "
                         "all temporary files will be removed.",
                         destName));
                failed = true;
                break;
            } else if (QFile(QDir::cleanPath(tdir.path() + '/' + file->name())).copy(destName)) {
                m_newFiles.append(destName);
                auto mimeType = mimeDb.mimeTypeForFile(destName);
                auto processMacros = mimeType.inherits(QStringLiteral("text/plain"));
                qCDebug(KAPPTEMPLATE) << (processMacros ? "processing file" : "not processing file") << destName << "with mimetype" << mimeType.name()
                                      << "inheriting" << mimeType.allAncestors();
                if (processMacros && !extractFileMacros(destName)) {
                    Q_EMIT errorOccurred(
                        i18n("Failed to integrate your project information into "
                             "the file %1. The project has not been generated and "
                             "all temporary files will be removed.",
                             destName));
                    failed = true;
                    break;
                }
            } else {
                Q_EMIT errorOccurred(i18n("Could not copy template file to %1.", destName));
                failed = true;
                break;
            }
        }
    }

    if (failed) {
        // Delete only newly created files
        for (int i = m_newFiles.size() - 1; i >= 0; --i) {
            const QString &dest = m_newFiles[i];
            QFileInfo fileInfo(dest);
            if (fileInfo.isDir()) {
                QDir().rmdir(dest);
            } else {
                QFile::remove(dest);
            }
            m_newFiles.removeAt(i);
        }
        return false;
    }

    return true;
}

bool Generator::extractFileMacros(const QString &entry)
{
    QFile file(entry);
    if (file.exists() && file.open(QFile::ReadOnly)) {
        auto input = QTextStream(&file).readAll();
        file.close();
        auto text = KMacroExpander::expandMacros(input, m_variables);

        if (text != input) {
            if (file.open(QFile::WriteOnly | QIODevice::Truncate)) {
                QTextStream output(&file);
                output << text;
                file.close();
                qCDebug(KAPPTEMPLATE) << "changed file written";
                return true;
            }
        } else {
            qCDebug(KAPPTEMPLATE) << "unchanged file not rewritten";
            return true;
        }
    }
    return false;
}

QStringList templateDirs()
{
    return QStandardPaths::locateAll(QStandardPaths::GenericDataLocation, "kdevappwizard/templates/", QStandardPaths::LocateDirectory);
}

QStringList Generator::templates()
{
    QStringList ret;
    const QStringList templatePaths = templateDirs();
    for (const QString &templatePath : templatePaths) {
        const auto templateArchives = QDir(templatePath).entryInfoList(QDir::Files);
        for (const auto &templateArchive : templateArchives) {
            ret << templateArchive.baseName();
        }
    }
    return ret;
}

void Generator::startGeneration(const QString &templateName, const QString &displayName)
{
    Prefs::setAppVersion(m_version);
    Prefs::setUrl(m_location);
    Prefs::setName(m_authorName);
    Prefs::setEmail(m_authorEmail);
    Prefs::setAppName(m_name);
    Prefs::self()->save();

    QString archName;
    const QStringList templatePaths = templateDirs();
    for (const QString &templatePath : templatePaths) {
        const auto templateArchives = QDir(templatePath).entryInfoList(QDir::Files);
        for (const auto &templateArchive : templateArchives) {
            const QString baseName = templateArchive.baseName();
            if (templateName.compare(baseName) == 0) {
                archName = templateArchive.absoluteFilePath();
                break;
            }
        }
    }

    if (archName.isEmpty()) {
        Q_EMIT errorOccurred(i18n("Could not load template archive for %1.", displayName));
        return;
    }

    // create dir where template project will be copied
    QString appName = m_name;

    QUrl projectUrl = QUrl::fromLocalFile(m_location).adjusted(QUrl::StripTrailingSlash);
    const QString url = projectUrl.toLocalFile();
    projectUrl.setPath(projectUrl.path() + QLatin1Char('/') + appName.toLower());
    const QString dest = projectUrl.toLocalFile();

    const QRegularExpression notWord(QStringLiteral("[^\\w]"));
    auto generateIdentifier = [&notWord](const QString &appname) {
        return QString(appname).replace(notWord, QStringLiteral("_"));
    };

    m_variables.clear();
    m_variables["CURRENT_YEAR"] = QString().setNum(QDate::currentDate().year());
    m_variables["APPNAME"] = appName;
    m_variables["APPNAMEUC"] = generateIdentifier(appName.toUpper()); // TODO: done by KDevelop, update docs here & ECM?
    m_variables["APPNAMELC"] = appName.toLower();
    m_variables["APPNAMEID"] = generateIdentifier(appName);
    m_variables["PROJECTDIR"] = dest;
    m_variables["PROJECTDIRNAME"] = projectUrl.fileName();
    m_variables["AUTHOR"] = m_authorName;
    m_variables["EMAIL"] = m_authorEmail;
    m_variables["VERSION"] = m_version;
    // deprecated
    m_variables["dest"] = dest;
    // undocumented & deprecated
    m_variables["APPNAMEFU"] = appName.replace(0, 1, appName.toUpper().at(0));
    m_variables["VERSIONCONTROLPLUGIN"] = QString(); // creation by kapptemplate is without VCS support/selection

    std::unique_ptr<KArchive> arch = nullptr;
    if (archName.endsWith(".zip")) {
        arch = std::make_unique<KZip>(archName);
    } else {
        arch = std::make_unique<KTar>(archName, "application/x-bzip");
    }

    if (arch->open(QIODevice::ReadOnly)) {
        // estimate metadata files which should not be copied
        QStringList metaDataFileNames;

        // try by same name
        const KArchiveEntry *templateEntry = arch->directory()->entry(templateName + QLatin1String(".kdevtemplate"));

        // but could be different name, if e.g. downloaded, so make a guess
        if (!templateEntry || !templateEntry->isFile()) {
            for (const auto &entryName : arch->directory()->entries()) {
                if (entryName.endsWith(QLatin1String(".kdevtemplate"))) {
                    templateEntry = arch->directory()->entry(entryName);
                    break;
                }
            }
        }

        if (templateEntry && templateEntry->isFile()) {
            metaDataFileNames << templateEntry->name();

            // check if a preview file is to be ignored
            const KArchiveFile *templateFile = static_cast<const KArchiveFile *>(templateEntry);
            QTemporaryDir temporaryDir;
            templateFile->copyTo(temporaryDir.path());

            KConfig config(temporaryDir.path() + QLatin1Char('/') + templateEntry->name());
            KConfigGroup group(&config, QStringLiteral("General"));
            if (group.hasKey("Icon")) {
                const KArchiveEntry *iconEntry = arch->directory()->entry(group.readEntry("Icon"));
                if (iconEntry && iconEntry->isFile()) {
                    metaDataFileNames << iconEntry->name();
                }
            }
        }

        if (!QFileInfo(dest).exists()) {
            QDir::root().mkdir(dest);
            qCDebug(KAPPTEMPLATE) << "Creating output directory:" << dest;
        }
        const auto ok = unpackArchive(arch->directory(), dest, metaDataFileNames);
        if (!ok) {
            return;
        }
    }

    QString resume;
    resume = i18n("Your project name is: <b>%1</b>, based on the <b>%2</b> template.<br />", appName, displayName);
    resume.append(i18n("Version: %1 <br /><br />", m_version));
    resume.append(i18n("Installed in: %1 <br /><br />", url));
    resume.append(i18n("You will find a README in your project folder <b>%1</b><br /> to help you get started with your project.", dest));
    Q_EMIT done(resume);
}
