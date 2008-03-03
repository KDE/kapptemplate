echo "Creating $LOCATION_ROOT/src/${APP_NAME_LC}_part.cpp...";
cat << EOF > $LOCATION_ROOT/src/${APP_NAME_LC}_part.cpp
#include "${APP_NAME_LC}_part.h"

#include "${APP_NAME_LC}_part.moc"

#include <kaction.h>
#include <kactioncollection.h>
#include <kcomponentdata.h>
#include <kfiledialog.h>
#include <kparts/genericfactory.h>
#include <kstandardaction.h>

#include <QtCore/QFile>
#include <QtCore/QTextStream>
#include <QtGui/QTextEdit>

typedef KParts::GenericFactory<${APP_NAME}Part> ${APP_NAME}PartFactory;
K_EXPORT_COMPONENT_FACTORY( lib${APP_NAME_LC}part, ${APP_NAME}PartFactory )

${APP_NAME}Part::${APP_NAME}Part( QWidget *parentWidget, QObject *parent, const QStringList & /*args*/ )
    : KParts::ReadWritePart(parent)
{
    // we need an instance
    setComponentData( ${APP_NAME}PartFactory::componentData() );

    // this should be your custom internal widget
    m_widget = new QTextEdit( parentWidget);

    // notify the part that this is our internal widget
    setWidget(m_widget);

    // create our actions
    KStandardAction::saveAs(this, SLOT(fileSaveAs()), actionCollection());
    save = KStandardAction::save(this, SLOT(save()), actionCollection());

    // set our XML-UI resource file
    setXMLFile("${APP_NAME_LC}_part.rc");

    // we are read-write by default
    setReadWrite(true);

    // we are not modified since we haven't done anything yet
    setModified(false);
}

${APP_NAME}Part::~${APP_NAME}Part()
{
}

void ${APP_NAME}Part::setReadWrite(bool rw)
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

void ${APP_NAME}Part::setModified(bool modified)
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

KAboutData *${APP_NAME}Part::createAboutData()
{
    // the non-i18n name here must be the same as the directory in
    // which the part's rc file is installed ('partrcdir' in the
    // Makefile)
    KAboutData *aboutData = new KAboutData("${APP_NAME_LC}part", 0, ki18n("${APP_NAME}Part"), "${APP_VERSION}");
    aboutData->addAuthor(ki18n("${AUTHOR}"), KLocalizedString(), "${EMAIL}");
    return aboutData;
}

bool ${APP_NAME}Part::openFile()
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

bool ${APP_NAME}Part::saveFile()
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

void ${APP_NAME}Part::fileSaveAs()
{
    // this slot is called whenever the File->Save As menu is selected,
    QString file_name = KFileDialog::getSaveFileName();
    if (file_name.isEmpty() == false)
        saveAs(file_name);
}

