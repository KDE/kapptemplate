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

#ifndef _APPTEMPLATESMODEL_H_
#define _APPTEMPLATESMODEL_H_

#include <QMap>
#include <QStandardItemModel>
#include <QVariant>
#include <QMap>

class ChoicePage;
class AppTemplateItem;

/**
 * @short Templates Model class
 * @author Anne-Marie Mahfouf <annma@kde.org>
 * @version 0.1
 */

class AppTemplatesModel: public QStandardItemModel {
public:
    AppTemplatesModel(ChoicePage *parent);
    // Refresh the model data
    void refresh();
    // Display the header
    QVariant headerData(int section, Qt::Orientation orientation, int role) const;

private:
    // Based on QStandardItem, create a model item 
    AppTemplateItem *createItem(const QString &name, const QString &category);
    // Instance of the view
    ChoicePage *m_choicePage;
    QMap<QString, QStandardItem*> m_templateItems;
};

#endif

