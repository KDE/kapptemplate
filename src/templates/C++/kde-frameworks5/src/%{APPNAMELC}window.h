/*
Copyright (C) %{CURRENT_YEAR} by %{AUTHOR} <%{EMAIL}>

This program is free software; you can redistribute it and/or
modify it under the terms of the GNU General Public License as
published by the Free Software Foundation; either version 2 of
the License or (at your option) version 3 or any later version
accepted by the membership of KDE e.V. (or its successor approved
by the membership of KDE e.V.), which shall act as a proxy 
defined in Section 14 of version 3 of the license.

This program is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
GNU General Public License for more details.

You should have received a copy of the GNU General Public License
along with this program.  If not, see <http://www.gnu.org/licenses/>.
*/

#ifndef %{APPNAMEUC}WINDOW_H
#define %{APPNAMEUC}WINDOW_H

#include <KXmlGuiWindow>

#include "ui_%{APPNAMELC}view.h"
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
