/***************************************************************************
 *   Copyright 2008 by Anne-Marie Mahfouf                             *
 *   annma@kde.org                                                         *
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

#include <kconfiggroup.h>
#include <KDebug>
#include <klocale.h>
#include <kstandarddirs.h>

#include "kapptemplate.h"
#include "apptemplatesmodel.h"
#include "apptemplateitem.h"

AppTemplatesModel::AppTemplatesModel(ChoicePage *parent)
    :QStandardItemModel(parent), m_choicePage(parent)
{
    kDebug() << "#######  create model" << endl;
}

void AppTemplatesModel::refresh()
{
    clear();
    //extractTemplateDescriptions();
    QStringList rootDirs;
    QStringList mdirs = KGlobal::dirs()->findDirs("data", "kapptemplate/");
    for (QStringList::Iterator it =mdirs.begin(); it !=mdirs.end(); ++it ) {
	QDir dir(*it);
	rootDirs += dir.entryList(QDir::Dirs, QDir::Name);
	rootDirs.removeAll(".");
	rootDirs.removeAll("..");
    }
    foreach (QString rootDir, rootDirs)
    {
        AppTemplateItem *templateItem = createCategoryItem(rootDir);

	QStringList mdirs = KGlobal::dirs()->findDirs("data", "kapptemplate/"+rootDir+"/");
	QStringList templatesDir;
	for (QStringList::Iterator it =mdirs.begin(); it !=mdirs.end(); ++it ) {
	    QDir dir(*it);
	    templatesDir += dir.entryList(QDir::Dirs, QDir::Name);
	    templatesDir.removeAll(".");
	    templatesDir.removeAll("..");
	}
	int i = 0;
	foreach (QString entry, templatesDir)
	{
	    AppTemplateItem *item = new AppTemplateItem(entry);
	    templateItem->setChild(i, item);
	    picture(item->index());
	    i++;
	}
    }
}

AppTemplateItem *AppTemplatesModel::createCategoryItem(const QString &name)
{
    QStandardItem *root = invisibleRootItem();
    AppTemplateItem *templateItem = new AppTemplateItem(name);
    root->appendRow(templateItem);
    templateItem->setFlags(Qt::ItemIsEnabled);
    return templateItem;
}

QVariant AppTemplatesModel::picture(const QModelIndex &index) const
{
    //get picture
    QString picPath = KStandardDirs::locate("data", QString("kapptemplate/C++/%1/%1.png").arg(index.data().toString()));
    QPixmap pixmap(picPath);
    //if pixmap null then display default pic
    return pixmap;
}

QVariant AppTemplatesModel::description(const QModelIndex &index) const
{
    //configure kapp4.txt
    QString descriptionPath = KStandardDirs::locate("data", QString("kapptemplate/C++/%1/description.txt").arg(index.data().toString()));
    QFile myFile;
    myFile.setFileName(descriptionPath);
    QFile openFileStream(myFile.fileName());
    openFileStream.open(QIODevice::ReadOnly);
    QTextStream readFileStr(&openFileStream);
    QString description = readFileStr.readAll();
    openFileStream.close();
    //if no description then display default string
    return description;
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
