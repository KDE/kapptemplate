/*
    SPDX-FileCopyrightText: 2008 Anne-Marie Mahfouf <annma@kde.org>

    SPDX-License-Identifier: GPL-2.0-or-later
*/

#include <KMacroExpander>

#include <QTest>
#include <QString>
#include <QTextStream>

#include "macrosubstitutiontest.h"

// This is a test to check the validity of the macros substitution.
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
    QCOMPARE(outputString, right);

    line = "#ifndef %{APPNAMEUC}_H";
    outputString = KMacroExpander::expandMacros(line, m_variables);
    right = "#ifndef KTRYAPP_H";
    QCOMPARE(outputString, right);

    line = "$XGETTEXT *.cpp -o $podir/%{APPNAMELC}.pot";
    outputString = KMacroExpander::expandMacros(line, m_variables);
    right = "$XGETTEXT *.cpp -o $podir/ktryapp.pot";
    QCOMPARE(outputString, right);

    line = "Copyright (C) 2007 %{AUTHOR} <%{EMAIL}>";
    outputString = KMacroExpander::expandMacros(line, m_variables);
    right = "Copyright (C) 2007 Foo Bar <foo@bar.org>";
    QCOMPARE(outputString, right);

    line = "Exec=%{APPNAMELC} %i -caption \"%c\"";
    outputString = KMacroExpander::expandMacros(line, m_variables);
    right = "Exec=ktryapp %i -caption \"%c\"";
    QCOMPARE(outputString, right);
}

QTEST_MAIN(MacroSubstitutionTest)
