/*
    SPDX-FileCopyrightText: 2007 Alexander Dymo <adymo@kdevelop.org>
    SPDX-FileCopyrightText: 2008 Anne-Marie Mahfouf <annma@kde.org>

    SPDX-License-Identifier: GPL-2.0-or-later
*/

#ifndef APPTEMPLATESMODEL_H
#define APPTEMPLATESMODEL_H

#include <QMap>
#include <QStandardItemModel>
#include <QVariant>
#include <qqmlregistration.h>

class ChoicePage;
class AppTemplateItem;

/**
 * @short Templates Model class
 * @author Anne-Marie Mahfouf <annma@kde.org>
 * @version 0.1
 */
class AppTemplatesModel: public QStandardItemModel
{
    Q_OBJECT
    QML_ELEMENT

public:
    enum TemplateRole
    {
        DescriptionFileRole = Qt::UserRole + 1,
        PictureNameRole = Qt::UserRole + 2,
        BaseNameRole = Qt::UserRole + 3
    };

    explicit AppTemplatesModel(QObject *parent = nullptr);

    /// Refresh the model data.
    Q_INVOKABLE void refresh();

    QVariant headerData(int section, Qt::Orientation orientation, int role) const override;
    QHash<int, QByteArray> roleNames() const override;

public Q_SLOTS:
    /// Load a template from a file.
    void loadFromFiles(const QStringList &selectedFiles);

private:
    // Based on QStandardItem, create a model item
    AppTemplateItem *createItem(const QString &name, const QString &category);
    QMap<QString, QStandardItem*> m_templateItems;
};

#endif // APPTEMPLATESMODEL_H

