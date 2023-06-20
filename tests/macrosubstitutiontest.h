/*
    SPDX-FileCopyrightText: 2008 Anne-Marie Mahfouf <annma@kde.org>

    SPDX-License-Identifier: GPL-2.0-or-later
*/

#ifndef MACROSUBSTITUTIONTEST_H
#define MACROSUBSTITUTIONTEST_H

#include <QHash>
#include <QObject>

class MacroSubstitutionTest : public QObject
{
    Q_OBJECT

private:
    QHash<QString, QString> m_variables;

private Q_SLOTS:
    void substitute();
};

#endif // MACROSUBSTITUTIONTEST_H
