/*
    SPDX-FileCopyrightText: %{CURRENT_YEAR} %{AUTHOR} <%{EMAIL}>

    SPDX-License-Identifier: GPL-2.0-only OR GPL-3.0-only OR LicenseRef-KDE-Accepted-GPL
*/

#ifndef %{APPNAMEUC}WINDOW_H
#define %{APPNAMEUC}WINDOW_H

#include <KXmlGuiWindow>

#include "ui_settings.h"
#include "%{APPNAME}Settings.h"

class %{APPNAME}View;

/**
 * This class serves as the main window for %{APPNAMELC}.  It handles the
 * menus, toolbars and status bars.
 *
 * @short Main window class
 * @author %{AUTHOR} <%{EMAIL}>
 * @version %{VERSION}
 */
class %{APPNAME}Window : public KXmlGuiWindow
{
    Q_OBJECT
public:
    /**
     * Default Constructor
     */
    %{APPNAME}Window();

    /**
     * Default Destructor
     */
    ~%{APPNAME}Window() override;

private Q_SLOTS:
    /**
     * Create a new window
     */
    void fileNew();

    /**
     * Open the settings dialog
     */
    void settingsConfigure();

private:
    // this is the name of the root widget inside our Ui file
    // you can rename it in designer and then change it here
    Ui::Settings m_settings;
    QAction *m_switchAction;
    %{APPNAME}View *m_%{APPNAMELC}View;
};

#endif // %{APPNAMEUC}WINDOW_H
