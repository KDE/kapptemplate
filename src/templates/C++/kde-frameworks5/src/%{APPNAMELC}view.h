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

#ifndef %{APPNAMEUC}VIEW_H
#define %{APPNAMEUC}VIEW_H

#include "ui_%{APPNAMELC}ViewBase.h"


/**
 * This class serves as the main window for %{APPNAMELC}.  It handles the
 * menus, toolbars and status bars.
 *
 * @short Main window class
 * @author %{AUTHOR} <%{EMAIL}>
 * @version %{VERSION}
 */
class %{APPNAME}View : public QWidget
{
    Q_OBJECT
public:
    /**
     * Default Constructor
     */
    explicit %{APPNAME}View(QWidget *parent);

    /**
     * Default Destructor
     */
    ~%{APPNAME}View() override;

public Q_SLOTS:
    void switchColors();
    void handleSettingsChanged();

private:
    // this is the name of the root widget inside our Ui file
    // you can rename it in designer and then change it here
    Ui::%{APPNAMELC}ViewBase m_ui;
};

#endif // %{APPNAMEUC}VIEW_H
