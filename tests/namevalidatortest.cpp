/*
    SPDX-FileCopyrightText: 2008 Anne-Marie Mahfouf <annma@kde.org>

    SPDX-License-Identifier: GPL-2.0-or-later
*/

#include <QTest>
#include <QRegExp>
#include <QString>

#include "namevalidatortest.h"

// This is a test to check the validity of the validator we use
// for entering a project application name. Foreign characters should be excluded
// as well as weird characters except _ . and -
void NameValidatorTest::testAppName()
{
    QRegExp rx("[a-zA-Z0-9_.\\-]*");
    QString myAppName = "KTry_App-0.1" ;
    bool ok = true;
    QCOMPARE(rx.exactMatch(myAppName), ok);
    QVERIFY(ok);
}

QTEST_MAIN(NameValidatorTest)
