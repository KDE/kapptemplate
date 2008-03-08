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

#include "macrosubstitutiontest.h"
#include <qtest_kde.h>
#include <kmacroexpander.h>
#include <kstandarddirs.h>
#include <QString>
#include <QTextStream>

QTEST_KDEMAIN_CORE(MacroSubstitutionTest)

// This is a test to check the validity of the macros
// substitution.
void MacroSubstitutionTest::substitute()
{
    QString appName = "KTryApp";
    QString authorName = "Foo Bar";
    QString email = "foo@bar.org";
    QString version = "0.1";
    m_variables.clear();
    m_variables["APPNAME"] = appName;
    m_variables["APPNAMEUC"] = appName.toUpper();
    m_variables["APPNAMELC"] = appName.toLower();
    m_variables["AUTHOR"] = authorName;
    m_variables["EMAIL"] = email;
    m_variables["VERSION"] = version;

    QString outputString;
    QString line = "File=%{APPNAME}.kcfg";
    outputString = KMacroExpander::expandMacros(line, m_variables);
    QString right = "File=KTryApp.kcfg";
    QCOMPARE(  outputString, right);

    line = "#ifndef %{APPNAMEUC}_H";
    outputString = KMacroExpander::expandMacros(line, m_variables);
    right = "#ifndef KTRYAPP_H";
    QCOMPARE(  outputString, right);

    line = "$XGETTEXT *.cpp -o $podir/%{APPNAMELC}.pot";
    outputString = KMacroExpander::expandMacros(line, m_variables);
    right = "$XGETTEXT *.cpp -o $podir/ktryapp.pot";
    QCOMPARE(  outputString, right);

    line = "Copyright (C) 2007 %{AUTHOR} <%{EMAIL}>";
    outputString = KMacroExpander::expandMacros(line, m_variables);
    right = "Copyright (C) 2007 Foo Bar <foo@bar.org>";
    QCOMPARE(  outputString, right);

    line = "Exec=%{APPNAMELC} %i -caption \"%c\"";
    outputString = KMacroExpander::expandMacros(line, m_variables);
    right = "Exec=ktryapp %i -caption \"%c\"";
    QCOMPARE(  outputString, right);
}

#include "macrosubstitutiontest.moc"
