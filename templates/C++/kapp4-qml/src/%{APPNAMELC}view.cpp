/***************************************************************************
 *   Copyright (C) %{CURRENT_YEAR} by %{AUTHOR} <%{EMAIL}>                            *
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
 *   51 Franklin Street, Fifth Floor, Boston, MA  02110-1301  USA .        *
 ***************************************************************************/

#include "%{APPNAMELC}view.h"
#include "settings.h"

#include <KLocale>
#include <KStandardDirs>

#include <QApplication>
#include <QtGui/QLabel>
#include <QGraphicsObject>
#include <QtDeclarative/QDeclarativeView>
#include <QtDeclarative/QDeclarativeProperty>
#include <QtDeclarative/QDeclarativeItem>

%{APPNAME}View::%{APPNAME}View(QWidget *)
{ 
    view = new QDeclarativeView(this);
    view->setSource(QUrl::fromLocalFile(KStandardDirs::locate("data", "%{APPNAMELC}/qml/main.qml")));
    kcfg_sillyLabel = view->rootObject();
    kcfg_sillyLabel->setProperty("width", width());
    QDeclarativeProperty(kcfg_sillyLabel, "width").write(width());
    kcfg_sillyLabel->setProperty("height", height());
    QDeclarativeProperty(kcfg_sillyLabel, "height").write(height());
    QObject::connect(kcfg_sillyLabel, SIGNAL(clicked()),
                      qApp, SLOT(quit()));
    view->show();
    settingsChanged();
}

%{APPNAME}View::~%{APPNAME}View()
{
}

void %{APPNAME}View::settingsChanged()
{
    QPalette pal;
    pal.setColor( QPalette::Window, Settings::col_background());
    pal.setColor( QPalette::WindowText, Settings::col_foreground());
    // Set the color from the Settings dialog to the foreground
    QDeclarativeProperty(kcfg_sillyLabel, "color").write(Settings::col_background());
    // Access the Text element from the QML file with its objectName
    QObject *kcfg_col_foreground = kcfg_sillyLabel->findChild<QObject*>("kcfg_col_foreground");
    // Set the Text color
    if (kcfg_col_foreground) {
        QDeclarativeProperty(kcfg_col_foreground, "color").write(Settings::col_foreground());
     }

    emit signalChangeStatusbar( i18n("Settings changed") );
}

void %{APPNAME}View::switchColors()
{
    // switch the foreground/background colors of the label
    QColor color = Settings::col_background();
    Settings::setCol_background( Settings::col_foreground() );
    Settings::setCol_foreground( color );

    settingsChanged();
}

#include "%{APPNAMELC}view.moc"
