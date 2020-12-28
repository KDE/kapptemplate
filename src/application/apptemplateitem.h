/*
    SPDX-FileCopyrightText: 2007 Alexander Dymo <adymo@kdevelop.org>
    SPDX-FileCopyrightText: 2008 Anne-Marie Mahfouf <annma@kde.org>

    SPDX-License-Identifier: GPL-2.0-or-later
*/

#ifndef APPTEMPLATEITEM_H
#define APPTEMPLATEITEM_H

#include <QStandardItem>

class AppTemplateItem: public QStandardItem
{
public:
    AppTemplateItem();
    explicit AppTemplateItem(const QString &text);
    AppTemplateItem(const QIcon &icon, const QString &text);
    explicit AppTemplateItem(int rows, int columns = 1);

private:
    void init();
};

#endif // APPTEMPLATEITEM_H

