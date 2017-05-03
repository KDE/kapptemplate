/***************************************************************************
 *   Copyright 2007 Alexander Dymo <adymo@kdevelop.org>                    *
 *   Copyright 2008 Anne-Marie Mahfouf <annma@kde.org>                     *
 *                                                                         *
 *   This program is free software; you can redistribute it and/or modify  *
 *   it under the terms of the GNU General Public License as published by  *
 *   the Free Software Foundation; either version 2 of the License, or     *
 *   (at your option) any later version.                                   *
 *                                                                         *
 *   This program is distributed in the hope that it will be useful,       *
 *   but WITHOUT ANY WARRANTY; without even the implied warranty of        *
 *   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the         *
 *   GNU General Public License for more details.                          *
 *                                                                         *
 *   You should have received a copy of the GNU General Public License     *
 *   along with this program; if not, write to the                         *
 *   Free Software Foundation, Inc.,                                       *
 *   51 Franklin Street, Fifth Floor, Boston, MA  02110-1301, USA.         *
 ***************************************************************************/

#include <KConfig>
#include <KConfigGroup>
#include <KLocalizedString>
#include <KTar>
#include <KZip>

#include <QStandardPaths>
#include <QDir>
#include <QFileInfo>

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
    foreach (const QString &templatePath, templatePaths) {
        foreach (const QString &templateArchive, QDir(templatePath).entryList(QDir::Files)) {
            templateArchives.append(templatePath + templateArchive);
        }
    }

    const QString templateDataBasePath = QStandardPaths::writableLocation(QStandardPaths::GenericDataLocation) + "/kdevappwizard/";
    const QString localDescriptionsDir = templateDataBasePath + "template_descriptions/";
    QDir dir(localDescriptionsDir);
    if (!dir.exists())
        dir.mkpath(localDescriptionsDir);

    foreach (const QString &archName, templateArchives) {
        qCDebug(KAPPTEMPLATE) << "processing template" << archName;
#ifdef Q_WS_WIN
        KZip templateArchive(archName);
#else
        KTar templateArchive(archName, "application/x-bzip");
#endif // Q_WS_WIN
        if (templateArchive.open(QIODevice::ReadOnly)) {
            QFileInfo templateInfo(archName);
            const KArchiveEntry *templateEntry = templateArchive.directory()->entry(templateInfo.baseName() + ".kdevtemplate");
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
            templateFile->copyTo(localDescriptionsDir);
        } else {
            qCDebug(KAPPTEMPLATE) << "could not open template" << archName;
        }
    }
}

void AppTemplatesModel::refresh()
{
    m_templateItems.clear();
    m_templateItems[""] = invisibleRootItem();

    extractTemplateDescriptions();

    QStringList templateArchives;
    const QString localDescriptionsDir = QStandardPaths::writableLocation(QStandardPaths::GenericDataLocation) + "/kdevappwizard/template_descriptions/";
    foreach (const QString &templateFile, QDir(localDescriptionsDir).entryList(QDir::Files)) {
        templateArchives.append(localDescriptionsDir + templateFile);
    }

    foreach (const QString &templateArchive, templateArchives) {
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
        templateItem->setData(description, Qt::UserRole + 1);
        templateItem->setData(picture, Qt::UserRole + 2);
        templateItem->setData(baseName, Qt::UserRole + 3);
    }
}

AppTemplateItem *AppTemplatesModel::createItem(const QString &name, const QString &category)
{
    QStringList path = category.split("/");

    QStandardItem *parent = invisibleRootItem();
    QStringList currentPath;
    foreach (const QString &entry, path) {
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
            return i18n("Templates Projects");
        default:
            break;
    }
    return QVariant();
}
