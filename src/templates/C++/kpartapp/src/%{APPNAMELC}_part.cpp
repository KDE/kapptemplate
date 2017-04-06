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

// KF headers
#include <KAboutData>
#include <KLocalizedString>
#include <KActionCollection>
#include <KPluginFactory>
#include <KStandardAction>

// Qt headers
#include <QFileDialog>
#include <QFile>
#include <QTextStream>
#include <QTextEdit>
#include <QTextDocument>

K_PLUGIN_FACTORY(%{APPNAME}PartFactory, registerPlugin<%{APPNAME}Part>();)

%{APPNAME}Part::%{APPNAME}Part(QWidget *parentWidget, QObject *parent, const QVariantList & /*args*/)
    : KParts::ReadWritePart(parent)
{
    // we need a component data
    setComponentData(createAboutData());

    // this should be your custom internal widget
    m_widget = new QTextEdit(parentWidget);

    // notify the part that this is our internal widget
    setWidget(m_widget);

    // create our actions
    KStandardAction::saveAs(this, SLOT(fileSaveAs()), actionCollection());
    m_saveAction = KStandardAction::save(this, SLOT(save()), actionCollection());

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

    QTextDocument* document = m_widget->document();
    if (rw) {
        connect(document, &QTextDocument::modificationChanged,
                this,     &%{APPNAME}Part::setModified);
    } else {
        disconnect(document, &QTextDocument::modificationChanged,
                   this,     &%{APPNAME}Part::setModified);
    }

    ReadWritePart::setReadWrite(rw);
}

void %{APPNAME}Part::setModified(bool modified)
{
    // get a handle on our Save action and make sure it is valid
    if (!m_saveAction) {
        return;
    }

    // if so, we either enable or disable it based on the current
    // state
    m_saveAction->setEnabled(modified);

    // in any event, we want our parent to do it's thing
    ReadWritePart::setModified(modified);
}

KAboutData %{APPNAME}Part::createAboutData()
{
    // the first arg here must be the same as the subdirectory in
    // which the part's rc file is installed
    KAboutData aboutData("%{APPNAMELC}part", i18n("%{APPNAME}Part"), QStringLiteral("%{VERSION}"));
    aboutData.addAuthor(i18n("%{AUTHOR}"), i18n("Author"), QStringLiteral("%{EMAIL}"));
    return aboutData;
}

bool %{APPNAME}Part::openFile()
{
    // localFilePath() is always local so we can use QFile on it
    QFile file(localFilePath());
    if (!file.open(QIODevice::ReadOnly | QIODevice::Text)) {
        return false;
    }

    // our example widget is text-based, so we use QTextStream instead
    // of a raw QDataStream
    QTextStream stream(&file);
    QString str;
    while (!stream.atEnd()) {
        str += stream.readLine() + "\n";
    }

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
    if (!isReadWrite()) {
        return false;
    }

    // localFilePath() is always local, so we use QFile
    QFile file(localFilePath());
    if (!file.open(QIODevice::ReadOnly | QIODevice::Text)) {
        return false;
    }

    // use QTextStream to dump the text to the file
    QTextStream stream(&file);
    stream << m_widget->document();

    file.close();

    m_widget->document()->setModified(false);

    return true;
}

void %{APPNAME}Part::fileSaveAs()
{
    // this slot is called whenever the File->Save As menu is selected,
    const QUrl file_name = QFileDialog::getSaveFileUrl();
    if (file_name.isValid()) {
        saveAs(file_name);
    }
}

// needed for K_PLUGIN_FACTORY
#include "%{APPNAMELC}_part.moc"
