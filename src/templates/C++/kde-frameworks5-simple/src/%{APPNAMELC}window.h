/*
    SPDX-FileCopyrightText: %{CURRENT_YEAR} %{AUTHOR} <%{EMAIL}>

    SPDX-License-Identifier: GPL-2.0-only OR GPL-3.0-only OR LicenseRef-KDE-Accepted-GPL
*/

#ifndef %{APPNAMEUC}WINDOW_H
#define %{APPNAMEUC}WINDOW_H


#include "ui_%{APPNAMELC}.h"

#include <QMainWindow>

/**
 * This class serves as the main window for %{APPNAME}.  It handles the
 * menus, toolbars and status bars.
 *
 * @short Main window class
 * @author %{AUTHOR} <%{EMAIL}>
 * @version %{VERSION}
 */
class %{APPNAME}Window : public QMainWindow
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

private:
    // this is the name of the root widget inside our Ui file
    // you can rename it in designer and then change it here
    Ui::mainWidget m_ui;
};

#endif // %{APPNAMEUC}WINDOW_H
