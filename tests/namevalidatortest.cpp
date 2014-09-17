/***************************************************************************
 *   Copyright 2008 by Anne-Marie Mahfouf                                  *
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
