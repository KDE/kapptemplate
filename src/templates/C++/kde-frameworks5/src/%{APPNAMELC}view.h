/*
    SPDX-FileCopyrightText: %{CURRENT_YEAR} %{AUTHOR} <%{EMAIL}>

    SPDX-License-Identifier: GPL-2.0-only OR GPL-3.0-only OR LicenseRef-KDE-Accepted-GPL
*/

#ifndef %{APPNAMEUC}VIEW_H
#define %{APPNAMEUC}VIEW_H

#include "ui_%{APPNAMELC}view.h"


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
    Ui::%{APPNAME}View m_ui;
};

#endif // %{APPNAMEUC}VIEW_H
