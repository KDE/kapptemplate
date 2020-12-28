/*
    SPDX-FileCopyrightText: 2007 Alexander Dymo <adymo@kdevelop.org>
    SPDX-FileCopyrightText: 2008 Anne-Marie Mahfouf <annma@kde.org>

    SPDX-License-Identifier: GPL-2.0-or-later
*/

#include <KConfig>
#include <KConfigGroup>
#include <KLocalizedString>
#include <KTar>
#include <KZip>

#include <QStandardPaths>
#include <QDir>
#include <QFileInfo>
#include <QTemporaryDir>

#include "choicepage.h"
#include "apptemplatesmodel.h"
#include "apptemplateitem.h"
#include "logging.h"

AppTemplatesModel::AppTemplatesModel(ChoicePage *parent)
    : QStandardItemModel(parent)
{
}

void extractTemplateDescriptions()
{
    QStringList templateArchives;
    const QStringList templatePaths = QStandardPaths::locateAll(QStandardPaths::GenericDataLocation, "/kdevappwizard/templates/", QStandardPaths::LocateDirectory);
    for (const QString &templatePath : qAsConst(templatePaths)) {
        const auto templateFiles = QDir(templatePath).entryList(QDir::Files);
        for (const QString &templateArchive : templateFiles) {
            templateArchives.append(templatePath + templateArchive);
        }
    }

    const QString templateDataBasePath = QStandardPaths::writableLocation(QStandardPaths::GenericDataLocation) + "/kdevappwizard/";
    const QString localDescriptionsDir = templateDataBasePath + "template_descriptions/";
    QDir dir(localDescriptionsDir);
    if (!dir.exists())
        dir.mkpath(localDescriptionsDir);

    for (const QString &archName : qAsConst(templateArchives)) {
        qCDebug(KAPPTEMPLATE) << "processing template" << archName;
#ifdef Q_WS_WIN
        KZip templateArchive(archName);
#else
        KTar templateArchive(archName, "application/x-bzip");
#endif // Q_WS_WIN
        if (templateArchive.open(QIODevice::ReadOnly)) {
            QFileInfo templateInfo(archName);
            const QString descriptionFileName = templateInfo.baseName() + QStringLiteral(".kdevtemplate");
            const KArchiveEntry *templateEntry = templateArchive.directory()->entry(descriptionFileName);
            // but could be different name, if e.g. downloaded, so make a guess
            if (!templateEntry || !templateEntry->isFile()) {
                for (const auto& entryName : templateArchive.directory()->entries()) {
                    if (entryName.endsWith(QLatin1String(".kdevtemplate"))) {
                        templateEntry = templateArchive.directory()->entry(entryName);
                        break;
                    }
                }
            }

            if (!templateEntry || !templateEntry->isFile()) {
                qCDebug(KAPPTEMPLATE) << "template" << archName << "does not contain .kdevtemplate file";
                continue;
            }
            const KArchiveFile *templateFile = (KArchiveFile*)templateEntry;

            qCDebug(KAPPTEMPLATE) << "copy template description to" << localDescriptionsDir;
            if (templateFile->name() == descriptionFileName) {
                templateFile->copyTo(localDescriptionsDir);
            } else {
                // Rename the extracted description
                // so that its basename matches the basename of the template archive
                // Use temporary dir to not overwrite other files with same name
                QTemporaryDir dir;
                templateFile->copyTo(dir.path());
                const QString destinationPath = localDescriptionsDir + descriptionFileName;
                QFile::remove(destinationPath);
                QFile::rename(dir.path() + QLatin1Char('/') + templateFile->name(), destinationPath);
            }
        } else {
            qCDebug(KAPPTEMPLATE) << "could not open template" << archName;
        }
    }
}

void AppTemplatesModel::refresh()
{
    clear();
    m_templateItems.clear();
    m_templateItems[""] = invisibleRootItem();

    extractTemplateDescriptions();

    QStringList templateArchives;
    const QString localDescriptionsDir = QStandardPaths::writableLocation(QStandardPaths::GenericDataLocation) + "/kdevappwizard/template_descriptions/";
    const auto templateFiles = QDir(localDescriptionsDir).entryList(QDir::Files);
    for (const QString &templateFile : templateFiles) {
        templateArchives.append(localDescriptionsDir + templateFile);
    }

    for (const QString &templateArchive : qAsConst(templateArchives)) {
        QFileInfo archiveInfo(templateArchive);
        QString baseName = archiveInfo.baseName();
        KConfig templateConfig(templateArchive);
        KConfigGroup general(&templateConfig, "General");
        QString name = general.readEntry("Name");
        QString category = general.readEntry("Category");
        qCDebug(KAPPTEMPLATE) << "category " << category;
        QString description = general.readEntry("Comment");
        QString picture = general.readEntry("Icon");
        AppTemplateItem *templateItem = createItem(name, category);
        templateItem->setData(description, DescriptionFileRole);
        templateItem->setData(picture, PictureNameRole);
        templateItem->setData(baseName, BaseNameRole);
    }
}

AppTemplateItem *AppTemplatesModel::createItem(const QString &name, const QString &category)
{
    const QStringList path = category.split(QLatin1Char('/'));

    QStandardItem *parent = invisibleRootItem();
    QStringList currentPath;
    for (const QString &entry : path) {
        currentPath << entry;
        qCDebug(KAPPTEMPLATE) << "current path " << currentPath;
        if (!m_templateItems.contains(currentPath.join("/"))) {
            AppTemplateItem *item = new AppTemplateItem(entry);
            parent->appendRow(item);
            m_templateItems[currentPath.join("/")] = item;
            parent = item;
        } else {
            parent = m_templateItems[currentPath.join("/")];
        }
    }

    AppTemplateItem *templateItem = new AppTemplateItem(name);
    parent->appendRow(templateItem);
    templateItem->setFlags(Qt::ItemIsSelectable | Qt::ItemIsEnabled);
    return templateItem;
}

// Set the column title (only 1 column in that case)
QVariant AppTemplatesModel::headerData(int section, Qt::Orientation orientation, int role) const
{
    Q_UNUSED(orientation);
    if (role != Qt::DisplayRole)
        return QVariant();

    switch (section) {
        case 0:
            return i18nc("@title:column", "Templates Projects");
        default:
            break;
    }
    return QVariant();
}
