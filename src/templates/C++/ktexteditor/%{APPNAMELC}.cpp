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

#include "%{APPNAMELC}.h"

#include <KTextEditor/Document>
#include <KTextEditor/Range>
#include <KTextEditor/View>
#include <KTextEditor/CodeCompletionInterface>
#include <KTextEditor/CodeCompletionInterface>
#include <KTextEditor/TextHintInterface>
#include <KTextEditor/MainWindow>

#include <KPluginFactory>
#include <KActionCollection>
#include <KLocalizedString>

#include <QAction>
#include <QFile>
#include <QDir>

K_PLUGIN_FACTORY_WITH_JSON(%{APPNAME}PluginFactory, "%{APPNAMELC}.json", registerPlugin<%{APPNAME}Plugin>();)

%{APPNAME}Plugin::%{APPNAME}Plugin(QObject *parent, const QList<QVariant> &) : KTextEditor::Plugin(parent)
{
}

%{APPNAME}Plugin::~%{APPNAME}Plugin()
{
}

QObject* %{APPNAME}Plugin::createView(KTextEditor::MainWindow *mainwindow)
{
    return new %{APPNAME}View(this, mainwindow);
}

%{APPNAME}View::%{APPNAME}View(%{APPNAME}Plugin *plugin, KTextEditor::MainWindow *mainwindow) : QObject(mainwindow)
{
    Q_UNUSED(plugin);
}

%{APPNAME}View::~%{APPNAME}View()
{
}

#include "%{APPNAMELC}.moc"
