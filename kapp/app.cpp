echo "Creating $LOCATION_ROOT/src/${APP_NAME_LC}.cpp...";
cat << EOF > $LOCATION_ROOT/src/${APP_NAME_LC}.cpp
/*
 * ${APP_NAME_LC}.cpp
 *
 * Copyright (C) 2007 $AUTHOR <$EMAIL>
 */
#include "${APP_NAME_LC}.h"
#include "${APP_NAME_LC}view.h"
#include "settings.h"

#include <qapplication.h>
#include <QtGui/QDragEnterEvent>
#include <QtGui/QPrinter>
#include <QtGui/QPrintDialog>
#include <QtGui/QDropEvent>
#include <QtGui/QPainter>

#include <kdeversion.h>
#include <kglobal.h>
#include <kiconloader.h>
#include <kmenubar.h>
#include <kstatusbar.h>
#include <kconfigdialog.h>
#include <kio/netaccess.h>
#include <kfiledialog.h>
#include <kurl.h>
#include <kurlrequesterdialog.h>
#include <kactioncollection.h>
#include <kaction.h>
#include <KLocale>

#include "${APP_NAME_LC}adaptor.h"
#include <QtDBus>

${APP_NAME}::${APP_NAME}()
    : KXmlGuiWindow( ),
      m_view(new ${APP_NAME}View(this)),
      m_printer(0)
{
    setObjectName(QLatin1String("${APP_NAME}"));
    // accept dnd
    setAcceptDrops(true);

    // tell the KXmlGuiWindow that this is indeed the main widget
    setCentralWidget(m_view);

    // then, setup our actions
    setupActions();

    // Add typical actions and save size/toolbars/statusbar
    setupGUI();

    // allow the view to change the statusbar and caption
    connect(m_view, SIGNAL(signalChangeStatusbar(const QString&)),
            this,   SLOT(changeStatusbar(const QString&)));
    connect(m_view, SIGNAL(signalChangeCaption(const QString&)),
            this,   SLOT(changeCaption(const QString&)));

    new ${APP_NAME}Adaptor(this);
    QDBusConnection::sessionBus().registerObject("/${APP_NAME_LC}", this);
}

${APP_NAME}::~${APP_NAME}()
{
    delete m_printer;
}

void ${APP_NAME}::load(const KUrl& url)
{
    QString target;
    // the below code is what you should normally do.  in this
    // example case, we want the url to our own.  you probably
    // want to use this code instead for your app

    #if 0
    // download the contents
    if (KIO::NetAccess::download(url, target))
    {
        // set our caption
        setCaption(url.prettyUrl());

        // load in the file (target is always local)
        loadFile(target);

        // and remove the temp file
        KIO::NetAccess::removeTempFile(target);
    }
    #endif

    setCaption(url.prettyUrl());
    m_view->openURL(url);
}

void ${APP_NAME}::setupActions()
{
    KStandardAction::openNew(this, SLOT(fileNew()), actionCollection());
    KStandardAction::open(this, SLOT(fileOpen()), actionCollection());
    KStandardAction::save(this, SLOT(fileSave()), actionCollection());
    KStandardAction::saveAs(this, SLOT(fileSaveAs()), actionCollection());
    KStandardAction::print(this, SLOT(filePrint()), actionCollection());
    KStandardAction::quit(qApp, SLOT(quit()), actionCollection());

    KStandardAction::preferences(this, SLOT(optionsPreferences()), actionCollection());

    // this doesn't do anything useful.  it's just here to illustrate
    // how to insert a custom menu and menu item
    KAction *custom = new KAction(i18n("Cus&tom Menuitem"), this);
    actionCollection()->addAction("custom_action", custom );
    connect(custom, SIGNAL(triggered(bool)), this, SLOT(optionsPreferences()));
}

void ${APP_NAME}::saveProperties(KConfigGroup &config)
{
    // the 'config' object points to the session managed
    // config file.  anything you write here will be available
    // later when this app is restored

    if (!m_view->currentURL().isNull()) {
        config.writePathEntry("lastURL", m_view->currentURL());
    }
}

void ${APP_NAME}::readProperties(const KConfigGroup &config)
{
    // the 'config' object points to the session managed
    // config file.  this function is automatically called whenever
    // the app is being restored.  read in here whatever you wrote
    // in 'saveProperties'

    QString url = config.readPathEntry("lastURL", QString());

    if (!url.isEmpty())
        m_view->openURL(KUrl::fromPathOrUrl(url));
}

void ${APP_NAME}::dragEnterEvent(QDragEnterEvent *)
{
    // accept uri drops only
    //event->accept(KURLDrag::canDecode(event));
}

void ${APP_NAME}::dropEvent(QDropEvent *event)
{
    // this is a very simplistic implementation of a drop event.  we
    // will only accept a dropped URL.  the Qt dnd code can do *much*
    // much more, so please read the docs there
    KUrl::List urls;

    // see if we can decode a URI.. if not, just ignore it
    KUrl::List uriList = KUrl::List::fromMimeData( event->mimeData() );
    if ( !uriList.isEmpty() )
    {
        // okay, we have a URI.. process it
        const KUrl &url = urls.first();

        // load in the file
        load(url);
    }
}

void ${APP_NAME}::fileNew()
{
    // this slot is called whenever the File->New menu is selected,
    // the New shortcut is pressed (usually CTRL+N) or the New toolbar
    // button is clicked

    // create a new window
    (new ${APP_NAME})->show();
}

void ${APP_NAME}::fileOpen()
{
    // this slot is called whenever the File->Open menu is selected,
    // the Open shortcut is pressed (usually CTRL+O) or the Open toolbar
    // button is clicked
    KUrl url = KUrlRequesterDialog::getUrl(QString::null, this, i18n("Open Location") );	//krazy:exclude=nullstrassign fr old broken gcc
    if (!url.isEmpty())
        m_view->openURL(url);
}

void ${APP_NAME}::fileSave()
{
    // this slot is called whenever the File->Save menu is selected,
    // the Save shortcut is pressed (usually CTRL+S) or the Save toolbar
    // button is clicked

    // save the current file
}

void ${APP_NAME}::fileSaveAs()
{
    // this slot is called whenever the File->Save As menu is selected,
    KUrl file_url = KFileDialog::getSaveUrl();
    if (!file_url.isEmpty() && file_url.isValid())
    {
        // save your info, here
    }
}

void ${APP_NAME}::filePrint()
{
    // this slot is called whenever the File->Print menu is selected,
    // the Print shortcut is pressed (usually CTRL+P) or the Print toolbar
    // button is clicked
    if (!m_printer) m_printer = new QPrinter;
    QPrintDialog dialog(m_printer, this);
    if (dialog.exec())
    {
        // setup the printer.  with Qt, you always "print" to a
        // QPainter.. whether the output medium is a pixmap, a screen,
        // or paper
        QPainter p;
        p.begin(m_printer);

        // we let our view do the actual printing
        m_view->print(&p, m_printer->height(), m_printer->width());

        // and send the result to the printer
        p.end();
    }
}

void ${APP_NAME}::optionsPreferences()
{
    //avoid to have 2 dialogs shown
    if ( KConfigDialog::showDialog( "settings" ) )  {
        return;
    }
    KConfigDialog *dialog = new KConfigDialog(this, "settings", Settings::self());
    QWidget *m_pageOne = new QWidget();
    dialog->addPage(m_pageOne, i18n("General"), "package_setting");
    connect(dialog, SIGNAL(settingsChanged(QString)), m_view, SLOT(settingsChanged()));
    //free mem by deleting the dialog on close without waiting for deletingit when the application quits
    dialog->setAttribute( Qt::WA_DeleteOnClose );

    dialog->show();
}

void ${APP_NAME}::changeStatusbar(const QString& text)
{
    // display the text on the statusbar
    statusBar()->showMessage(text);
}

void ${APP_NAME}::changeCaption(const QString& text)
{
    // display the text on the caption
    setCaption(text);
}

#include "${APP_NAME_LC}.moc"
