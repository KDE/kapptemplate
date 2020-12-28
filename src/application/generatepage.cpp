/*
    SPDX-FileCopyrightText: 2001 Bernd Gehrmann <bernd@kdevelop.org>
    SPDX-FileCopyrightText: 2004-2005 Sascha Cunz <sascha@kdevelop.org>
    SPDX-FileCopyrightText: 2007 Alexander Dymo <adymo@kdevelop.org>
    SPDX-FileCopyrightText: 2008 Anne-Marie Mahfouf <annma@kde.org>

    SPDX-License-Identifier: GPL-2.0-or-later
*/

#include <KLocalizedString>
#include <KMacroExpander>
#include <KMessageBox>
#include <KTar>
#include <KZip>
#include <KIO/CopyJob>

#include <QTemporaryDir>
#include <QDir>
#include <QFileInfo>
#include <QTextCodec>

#include "kapptemplate.h"
#include "generatepage.h"
#include "prefs.h"
#include "logging.h"

GeneratePage::GeneratePage(QWidget *parent)
    : QWizardPage(parent)
{
    setTitle(i18n("Generating your project"));
    ui_generate.setupUi(this);
}

bool GeneratePage::unpackArchive(const KArchiveDirectory *dir, const QString &dest, const QStringList& skipList)
{
    qCDebug(KAPPTEMPLATE) << "unpacking dir:" << dir->name() << "to" << dest;
    const QStringList entries = dir->entries();
    qCDebug(KAPPTEMPLATE) << "entries:" << entries.join(",");

    QTemporaryDir tdir;

    bool ret = true;

    //create path were we want copy files to
    if (!QDir::root().mkpath(dest)) {
        displayError(i18n("%1 cannot be created.", dest));
        return false;
    }

    int progress = 0;

    bool failed = false;
    for (const QString &entry : entries) {
        progress++;
        ui_generate.progressBar->setValue((progress / entries.size()) * 100);

        if (skipList.contains(entry)) {
            continue;
        }

        if (dir->entry(entry)->isDirectory()) {
            const KArchiveDirectory *file = dynamic_cast<const KArchiveDirectory *>(dir->entry(entry));
            QString newdest = dest + "/" + file->name();
            if (!QFileInfo(newdest).exists()) {
                if (!QDir::root().mkdir(newdest)) {
                    displayError(i18n("Path %1 could not be created.", newdest));
                    return false;
                }
            }
            ret |= unpackArchive(file, newdest);
        }
        else if (dir->entry(entry)->isFile()) {
            const KArchiveFile *file = dynamic_cast<const KArchiveFile *>(dir->entry(entry));
            file->copyTo(tdir.path());
            QString destName = KMacroExpander::expandMacros(dest + '/' + file->name(), m_variables);
            if (QFile(QDir::cleanPath(tdir.path() + '/' + file->name())).copy(destName)) {
                if (!extractFileMacros(destName)) {
                    displayError(i18n("Failed to integrate your project information into "
                                      "the file %1. The project has not been generated and "
                                      "all temporary files will be removed.", destName));
                    failed = true;
                    break;
                }
            } else {
                displayError(i18n("Could not copy template file to %1.", destName));
                failed = true;
                break;
            }
        }
    }

    if (failed && !QDir(dest).removeRecursively()) {
        qCDebug(KAPPTEMPLATE) << "Failed to remove incomplete destination directory" << dest;
    }

    return ret;
}

bool GeneratePage::extractFileMacros(const QString &entry)
{
    QString text;
    QFile file(entry);
    if(file.exists() && file.open(QFile::ReadOnly)) {
        QTextStream input(&file);
        text = KMacroExpander::expandMacros(input.readAll(), m_variables);
        file.close();
        if(file.open(QFile::WriteOnly | QIODevice::Truncate)) {
            QTextStream output(&file);
            output << text;
            file.close();
            return true;
        }
    }
    return false;
}

void GeneratePage::initializePage()
{
    feedback = i18n("Generation Progress\n");
    ui_generate.label->setText(feedback);
    templateName = field("tempName").toString();
    if (templateName.isEmpty()) {
        templateName = "kde4";
    }

    QString archName;
    const QStringList templatePaths = QStandardPaths::locateAll(QStandardPaths::GenericDataLocation, "/kdevappwizard/templates/", QStandardPaths::LocateDirectory);
    for (const QString &templatePath : templatePaths) {
        const auto templateArchives = QDir(templatePath).entryList(QDir::Files);
        for (const QString &templateArchive : templateArchives) {
            const QString baseName = QFileInfo(templateArchive).baseName();
            if (templateName.compare(baseName) == 0) {
                archName = templatePath + templateArchive;
                break;
            }
        }
    }

    if (archName.isEmpty())
        return;

    //create dir where template project will be copied
    QString appName = field("appName").toString();
    QString version = field("version").toString();

    QString url = field("url").toString();
    if (url.endsWith(QLatin1Char('/'))) {
        url.chop(1);
    }
    QString dest(url + '/' + appName.toLower());

    m_variables.clear();
    m_variables["CURRENT_YEAR"] = QString().setNum(QDate::currentDate().year());
    m_variables["APPNAME"] = appName;
    m_variables["APPNAMEUC"] = appName.toUpper();
    m_variables["APPNAMELC"] = appName.toLower();
    m_variables["AUTHOR"] = field("author").toString();
    m_variables["EMAIL"] = field("email").toString();
    m_variables["VERSION"] = version;
    m_variables["PROJECTDIRNAME"] = appName.toLower();
    // deprecated
    m_variables["dest"] = dest;
    // undocumented & deprecated
    m_variables["APPNAMEFU"] = appName.replace(0, 1, appName.toUpper().at(0));
    m_variables["VERSIONCONTROLPLUGIN"] = QString(); // creation by kapptemplate is without VCS support/selection


    KArchive* arch = nullptr;
    if (archName.endsWith(".zip")) {
        arch = new KZip(archName);
    } else {
        arch = new KTar(archName, "application/x-bzip");
    }

    if (arch->open(QIODevice::ReadOnly)) {
        // estimate metadata files which should not be copied
        QStringList metaDataFileNames;

        // try by same name
        const KArchiveEntry *templateEntry =
            arch->directory()->entry(templateName + QLatin1String(".kdevtemplate"));

        // but could be different name, if e.g. downloaded, so make a guess
        if (!templateEntry || !templateEntry->isFile()) {
            for (const auto& entryName : arch->directory()->entries()) {
                if (entryName.endsWith(QLatin1String(".kdevtemplate"))) {
                    templateEntry = arch->directory()->entry(entryName);
                    break;
                }
            }
        }

        if (templateEntry && templateEntry->isFile()) {
            metaDataFileNames << templateEntry->name();

            // check if a preview file is to be ignored
            const KArchiveFile *templateFile = static_cast<const KArchiveFile*>(templateEntry);
            QTemporaryDir temporaryDir;
            templateFile->copyTo(temporaryDir.path());

            KConfig config(temporaryDir.path() + QLatin1Char('/') + templateEntry->name());
            KConfigGroup group(&config, "General");
            if (group.hasKey("Icon")) {
                const KArchiveEntry* iconEntry = arch->directory()->entry(group.readEntry("Icon"));
                if (iconEntry && iconEntry->isFile()) {
                    metaDataFileNames << iconEntry->name();
                }
            }
        }

        if (!QFileInfo(dest).exists()) {
            QDir::root().mkdir(dest);
            qCDebug(KAPPTEMPLATE) << "Creating output directory:" << dest;
        }

        unpackArchive(arch->directory(), dest, metaDataFileNames);
    }
    delete arch;

    feedback.append(i18n("Succeeded.\n"));
    ui_generate.label->setText(feedback);

    QString resume;
    resume = i18n("Your project name is: <b>%1</b>, based on the %2 template.<br />", appName, templateName);
    resume.append(i18n("Version: %1 <br /><br />", version));
    resume.append(i18n("Installed in: %1 <br /><br />", url));
    resume.append(i18n("You will find a README in your project folder <b>%1</b><br /> to help you get started with your project.", url + '/' + appName.toLower()));
    ui_generate.summaryLabel->setText(resume);
}

void GeneratePage::displayError(const QString &error)
{
    KMessageBox::sorry(nullptr, error, i18nc("@title:window", "Error"));
    feedback.append("\n\n" + error);
    ui_generate.label->setText(feedback);
}
