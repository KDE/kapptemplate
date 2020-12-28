/*
    SPDX-FileCopyrightText: 2007 Alexander Dymo <adymo@kdevelop.org>
    SPDX-FileCopyrightText: 2008 Anne-Marie Mahfouf <annma@kde.org>

    SPDX-License-Identifier: GPL-2.0-or-later
*/

#ifndef APPTEMPLATESMODEL_H
#define APPTEMPLATESMODEL_H

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
class AppTemplatesModel: public QStandardItemModel
{
public:
    enum TemplateRole
    {
        DescriptionFileRole = Qt::UserRole + 1,
        PictureNameRole = Qt::UserRole + 2,
        BaseNameRole = Qt::UserRole + 3
    };

    explicit AppTemplatesModel(ChoicePage *parent);
    // Refresh the model data
    void refresh();
    // Display the header
    QVariant headerData(int section, Qt::Orientation orientation, int role) const override;

private:
    // Based on QStandardItem, create a model item
    AppTemplateItem *createItem(const QString &name, const QString &category);
    QMap<QString, QStandardItem*> m_templateItems;
};

#endif // APPTEMPLATESMODEL_H

