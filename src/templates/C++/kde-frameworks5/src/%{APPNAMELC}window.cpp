/*
    SPDX-FileCopyrightText: %{CURRENT_YEAR} %{AUTHOR} <%{EMAIL}>

    SPDX-License-Identifier: GPL-2.0-only OR GPL-3.0-only OR LicenseRef-KDE-Accepted-GPL
*/

// application headers
#include "%{APPNAMELC}window.h"

#include "%{APPNAMELC}view.h"
#include "%{APPNAMELC}debug.h"

// KF headers
#include <KActionCollection>
#include <KConfigDialog>


%{APPNAME}Window::%{APPNAME}Window()
    : KXmlGuiWindow()
{
    m_%{APPNAMELC}View = new %{APPNAME}View(this);
    setCentralWidget(m_%{APPNAMELC}View);

    KActionCollection* actionCollection = this->actionCollection();
    m_switchAction = actionCollection->addAction(QStringLiteral("switch_action"));
    m_switchAction->setText(i18nc("@action", "Switch Colors"));
    m_switchAction->setIcon(QIcon::fromTheme(QStringLiteral("fill-color")));
    connect(m_switchAction, &QAction::triggered, m_%{APPNAMELC}View, &%{APPNAME}View::switchColors);

    KStandardAction::openNew(this, SLOT(fileNew()), actionCollection);
    KStandardAction::quit(qApp, SLOT(closeAllWindows()), actionCollection);
    KStandardAction::preferences(this, SLOT(settingsConfigure()), actionCollection);

    setupGUI();
}

%{APPNAME}Window::~%{APPNAME}Window()
{
}

void %{APPNAME}Window::fileNew()
{
    qCDebug(%{APPNAMEUC}) << "%{APPNAME}Window::fileNew()";
    (new %{APPNAME}Window)->show();
}

void %{APPNAME}Window::settingsConfigure()
{
    qCDebug(%{APPNAMEUC}) << "%{APPNAME}Window::settingsConfigure()";
    // The preference dialog is derived from prefs_base.ui
    //
    // compare the names of the widgets in the .ui file
    // to the names of the variables in the .kcfg file
    //avoid to have 2 dialogs shown
    if (KConfigDialog::showDialog(QStringLiteral("settings"))) {
        return;
    }

    KConfigDialog *dialog = new KConfigDialog(this, QStringLiteral("settings"), %{APPNAME}Settings::self());
    QWidget *generalSettingsPage = new QWidget;
    m_settings.setupUi(generalSettingsPage);
    dialog->addPage(generalSettingsPage, i18nc("@title:tab", "General"), QStringLiteral("package_setting"));
    connect(dialog, &KConfigDialog::settingsChanged, m_%{APPNAMELC}View, &%{APPNAME}View::handleSettingsChanged);
    dialog->setAttribute(Qt::WA_DeleteOnClose);
    dialog->show();
}
