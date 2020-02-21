/*
    SPDX-FileCopyrightText: %{CURRENT_YEAR} %{AUTHOR} <%{EMAIL}>

    SPDX-License-Identifier: GPL-2.0-only OR GPL-3.0-only OR LicenseRef-KDE-Accepted-GPL
*/

// application headers
#include "%{APPNAMELC}view.h"

#include "%{APPNAME}Settings.h"
#include "%{APPNAMELC}debug.h"


%{APPNAME}View::%{APPNAME}View(QWidget *parent)
    : QWidget(parent)
{
    m_ui.setupUi(this);
    handleSettingsChanged();
}

%{APPNAME}View::~%{APPNAME}View()
{
}

void %{APPNAME}View::switchColors()
{
    // switch the foreground/background colors of the label
    QColor color = %{APPNAME}Settings::colorBackground();
    %{APPNAME}Settings::setColorBackground(%{APPNAME}Settings::colorForeground());
    %{APPNAME}Settings::setColorForeground(color);

    handleSettingsChanged();
}

void %{APPNAME}View::handleSettingsChanged()
{
    qCDebug(%{APPNAMEUC}) << "%{APPNAME}View::handleSettingsChanged()";
    QPalette palette = m_ui.templateLabel->palette();
    palette.setColor(QPalette::Window, %{APPNAME}Settings::colorBackground());
    palette.setColor(QPalette::WindowText, %{APPNAME}Settings::colorForeground());
    m_ui.templateLabel->setPalette(palette);

    // i18n : internationalization
    m_ui.templateLabel->setText(i18n("This project is %1 days old", %{APPNAME}Settings::ageInDays()));
}

