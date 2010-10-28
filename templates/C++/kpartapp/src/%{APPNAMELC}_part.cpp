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

#include "%{APPNAMELC}_part.h"

#include "%{APPNAMELC}_part.moc"

#include <kaction.h>
#include <kactioncollection.h>
#include <kcomponentdata.h>
#include <kfiledialog.h>
#include <kparts/genericfactory.h>
#include <kstandardaction.h>

#include <QtCore/QFile>
#include <QtCore/QTextStream>
#include <QtGui/QTextEdit>

typedef KParts::GenericFactory<%{APPNAME}Part> %{APPNAME}PartFactory;
K_EXPORT_COMPONENT_FACTORY( lib%{APPNAMELC}part, %{APPNAME}PartFactory )

%{APPNAME}Part::%{APPNAME}Part( QWidget *parentWidget, QObject *parent, const QStringList & /*args*/ )
    : KParts::ReadWritePart(parent)
{
    // we need an instance
    setComponentData( %{APPNAME}PartFactory::componentData() );

    // this should be your custom internal widget
    m_widget = new QTextEdit( parentWidget);

    // notify the part that this is our internal widget
    setWidget(m_widget);

    // create our actions
    KStandardAction::saveAs(this, SLOT(fileSaveAs()), actionCollection());
    save = KStandardAction::save(this, SLOT(save()), actionCollection());

    // set our XML-UI resource file
    setXMLFile("%{APPNAMELC}_part.rc");

    // we are read-write by default
    setReadWrite(true);

    // we are not modified since we haven't done anything yet
    setModified(false);
}

%{APPNAME}Part::~%{APPNAME}Part()
{
}

void %{APPNAME}Part::setReadWrite(bool rw)
{
    // notify your internal widget of the read-write state
    m_widget->setReadOnly(!rw);
    if (rw)
        connect(m_widget, SIGNAL(textChanged()),
                this,     SLOT(setModified()));
    else
    {
        disconnect(m_widget, SIGNAL(textChanged()),
                   this,     SLOT(setModified()));
    }

    ReadWritePart::setReadWrite(rw);
}

void %{APPNAME}Part::setModified(bool modified)
{
    // get a handle on our Save action and make sure it is valid
    if (!save)
        return;

    // if so, we either enable or disable it based on the current
    // state
    if (modified)
        save->setEnabled(true);
    else
        save->setEnabled(false);

    // in any event, we want our parent to do it's thing
    ReadWritePart::setModified(modified);
}

KAboutData *%{APPNAME}Part::createAboutData()
{
    // the non-i18n name here must be the same as the directory in
    // which the part's rc file is installed ('partrcdir' in the
    // Makefile)
    KAboutData *aboutData = new KAboutData("%{APPNAMELC}part", "%{APPNAMELC}", ki18n("%{APPNAME}Part"), "%{VERSION}");
    aboutData->addAuthor(ki18n("%{AUTHOR}"), KLocalizedString(), "%{EMAIL}");
    return aboutData;
}

bool %{APPNAME}Part::openFile()
{
    // m_file is always local so we can use QFile on it
    QFile file("m_file");
    if (!file.open(QIODevice::ReadOnly | QIODevice::Text))
        return false;

    // our example widget is text-based, so we use QTextStream instead
    // of a raw QDataStream
    QTextStream stream(&file);
    QString str;
    while (!stream.atEnd())
        str += stream.readLine() + "\n";

    file.close();

    // now that we have the entire file, display it
    m_widget->setPlainText(str);

    // just for fun, set the status bar
    //emit setStatusBarText( m_url.prettyUrl() );

    return true;
}

bool %{APPNAME}Part::saveFile()
{
    // if we aren't read-write, return immediately
    if (isReadWrite() == false)
        return false;

    // m_file is always local, so we use QFile
    QFile file("m_file");
    if (!file.open(QIODevice::ReadOnly | QIODevice::Text))
        return false;

    // use QTextStream to dump the text to the file
    QTextStream stream(&file);
    stream << m_widget->document();

    file.close();

    return true;
}

void %{APPNAME}Part::fileSaveAs()
{
    // this slot is called whenever the File->Save As menu is selected,
    QString file_name = KFileDialog::getSaveFileName();
    if (file_name.isEmpty() == false)
        saveAs(file_name);
}

