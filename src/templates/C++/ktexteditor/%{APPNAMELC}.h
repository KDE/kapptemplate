/***************************************************************************
 *   Copyright (C) %{CURRENT_YEAR} by %{AUTHOR} <%{EMAIL}>                 *
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

#ifndef %{APPNAMEUC}_H
#define %{APPNAMEUC}_H

#include <KTextEditor/Plugin>
#include <KTextEditor/Range>
#include <KTextEditor/TextHintInterface>

#include <QVariantList>
#include <QList>

#include <KXMLGUIClient>

class %{APPNAME}Plugin;

class %{APPNAME}Plugin : public KTextEditor::Plugin
{
    Q_OBJECT

public:
    explicit %{APPNAME}Plugin(QObject *parent = 0, const QList<QVariant> & = QList<QVariant>());
    virtual ~%{APPNAME}Plugin();
    QObject *createView(KTextEditor::MainWindow *mainWindow);
};

class %{APPNAME}View: public QObject
{
    Q_OBJECT

public:
    %{APPNAME}View(%{APPNAME}Plugin *plugin, KTextEditor::MainWindow *view);
    virtual ~%{APPNAME}View();
};

#endif // %{APPNAMEUC}
