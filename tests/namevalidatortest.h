/*
    SPDX-FileCopyrightText: 2008 Anne-Marie Mahfouf <annma@kde.org>

    SPDX-License-Identifier: GPL-2.0-or-later
*/

#ifndef NAMEVALIDATORTEST_H
#define NAMEVALIDATORTEST_H

#include <QObject>

class NameValidatorTest : public QObject
{
    Q_OBJECT

private Q_SLOTS:
    void testAppName();
};

#endif // NAMEVALIDATORTEST_H
