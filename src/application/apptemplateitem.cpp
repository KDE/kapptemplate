/*
    SPDX-FileCopyrightText: 2007 Alexander Dymo <adymo@kdevelop.org>
    SPDX-FileCopyrightText: 2008 Anne-Marie Mahfouf <annma@kde.org>

    SPDX-License-Identifier: GPL-2.0-or-later
*/

#include "apptemplateitem.h"

AppTemplateItem::AppTemplateItem()
    : QStandardItem()
{
    init();
}

AppTemplateItem::AppTemplateItem(const QIcon & icon, const QString & text)
    : QStandardItem(icon, text)
{
    init();
}

AppTemplateItem::AppTemplateItem(const QString & text)
    : QStandardItem(text)
{
    init();
}

AppTemplateItem::AppTemplateItem(int rows, int columns)
    : QStandardItem(rows, columns)
{
    init();
}

void AppTemplateItem::init()
{
    setFlags(Qt::ItemIsEnabled);
}
