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

#include <QFileInfo>

#include <kconfiggroup.h>
#include <KDebug>
#include <klocale.h>
#include <kstandarddirs.h>

#include "choicepage.h"
#include "apptemplatesmodel.h"
#include "apptemplateitem.h"

AppTemplatesModel::AppTemplatesModel(ChoicePage *parent)
    :QStandardItemModel(parent), m_choicePage(parent)
{
}

void AppTemplatesModel::refresh()
{
    m_templateItems.clear();
    m_templateItems[""] = invisibleRootItem();
    //find all .kdevtemplate files on the system
    QStringList templateArchives = KGlobal::dirs()->findAllResources("data", "kdevappwizard/template_descriptions/*.kdevtemplate");
    QStringList tempList;
    foreach (const QString &templateArchive, templateArchives)
    {
	QFileInfo archiveInfo(templateArchive);
	QString baseName = archiveInfo.baseName();
        KConfig templateConfig(templateArchive);
        KConfigGroup general(&templateConfig, "General");
        QString name = general.readEntry("Name");
        QString category = general.readEntry("Category");
	kDebug() << "category " << category << endl;
	QString description = general.readEntry("Comment");
	QString picture = general.readEntry("Icon");
	AppTemplateItem *templateItem = createItem(name, category);
	templateItem->setData(description, Qt::UserRole+1);
	templateItem->setData(picture, Qt::UserRole+2);
	templateItem->setData(baseName, Qt::UserRole+3);
    }
}

AppTemplateItem *AppTemplatesModel::createItem(const QString &name, const QString &category)
{
    QStringList path = category.split("/");

    QStandardItem *parent = invisibleRootItem();
    QStringList currentPath;
    foreach (const QString &entry, path)
    {
        currentPath << entry;
	kDebug() << "current path " << currentPath << endl;
        if (!m_templateItems.contains(currentPath.join("/")))
        {
	    kDebug() << "in if " << endl;
            AppTemplateItem *item = new AppTemplateItem(entry);
            parent->appendRow(item);
            m_templateItems[currentPath.join("/")] = item;
            parent = item;
        }
        else
            parent = m_templateItems[currentPath.join("/")];
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

