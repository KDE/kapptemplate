echo "Creating $LOCATION_ROOT/${APP_NAME_LC}/${APP_NAME_LC}.cpp...";
cat << EOF > $LOCATION_ROOT/${APP_NAME_LC}/${APP_NAME_LC}.cpp
/*
 * ${APP_NAME_LC}.cpp
 *
 * Copyright (C) 2000 $AUTHOR <$EMAIL>
 */
#include "${APP_NAME_LC}.h"

#include "${APP_NAME_LC}pref.h"

#include <qdragobject.h>
#include <qlineedit.h>
#include <qprinter.h>
#include <qprintdialog.h>
#include <qpainter.h>
#include <qpaintdevicemetrics.h>

#include <kglobal.h>
#include <klocale.h>
#include <kiconloader.h>
#include <kmenubar.h>
#include <kkeydialog.h>
#include <kaccel.h>
#include <kio/netaccess.h>
#include <kfiledialog.h>
#include <kconfig.h>
#include <kurl.h>

#include <kdialogbase.h>

#include <kstdaccel.h>
#include <kaction.h>
#include <kstdaction.h>

${APP_NAME}::${APP_NAME}()
    : m_view(new ${APP_NAME}View(this)),
      m_printer(0),
      m_accelKeys(new KAccel(this))
{
    // accept dnd
    setAcceptDrops(true);

    // tell the KTMainWindow that this is indeed the main widget
    setView(m_view);

    // first, setup our accel keys
    setupAccel();

    // then, setup our actions
    setupActions();

    // and a status bar
    enableStatusBar();

    // allow the view to change the statusbar and caption
    connect(m_view, SIGNAL(signalChangeStatusbar(const QString&)),
            this,   SLOT(changeStatusbar(const QString&)));
    connect(m_view, SIGNAL(signalChangeCaption(const QString&)),
            this,   SLOT(changeCaption(const QString&)));

}

${APP_NAME}::~${APP_NAME}()
{
}

void ${APP_NAME}::load(const QString& url)
{
    QString target;
    // the below code is what you should normally do.  in this
    // example case, we want the url to our own.  you probably
    // want to use this code instead for your app

    #if 0
    // download the contents
    if (KIONetAccess::download(url, target))
    {
        // set our caption
        setCaption(url);

        // load in the file (target is always local)
        loadFile(target);

        // and remove the temp file
        KIONetAccess::removeTempFile(target);
    }
    #endif

    setCaption(url);
    m_view->openURL(url.ascii());
}

void ${APP_NAME}::setupAccel()
{
    // insert all of our std accel so that they show up in the
    // config dialog
    m_accelKeys->insertStdItem(KStdAccel::New);
    m_accelKeys->insertStdItem(KStdAccel::Open);
    m_accelKeys->insertStdItem(KStdAccel::Save);
    m_accelKeys->insertStdItem(KStdAccel::Print);
    m_accelKeys->insertStdItem(KStdAccel::Quit);
    m_accelKeys->insertStdItem(KStdAccel::Help);

    // we need to read in the default settings now.  if we do it
    // before the 'connectItem' calls or after the 'changeMenuAccel'
    // calls, the settings will have no effect!
    m_accelKeys->readSettings();
}

void ${APP_NAME}::setupActions()
{
    KStdAction::openNew(this, SLOT(fileNew()), actionCollection());
    KStdAction::open(this, SLOT(fileOpen()), actionCollection());
    KStdAction::save(this, SLOT(fileSave()), actionCollection());
    KStdAction::saveAs(this, SLOT(fileSaveAs()), actionCollection());
    KStdAction::print(this, SLOT(filePrint()), actionCollection());
    KStdAction::quit(kapp, SLOT(quit()), actionCollection());

    KStdAction::showToolbar(this, SLOT(optionsShowToolbar()), actionCollection());
    KStdAction::showStatusbar(this, SLOT(optionsShowStatusbar()), actionCollection());

    KStdAction::keyBindings(this, SLOT(optionsConfigure()), actionCollection());
    KStdAction::preferences(this, SLOT(optionsPreferences()), actionCollection());

    createGUI();
}

void ${APP_NAME}::saveProperties(KConfig *config)
{
    // the 'config' object points to the session managed
    // config file.  anything you write here will be available
    // later when this app is restored
    
    if (m_view->currentURL() != QString::null)
        config->writeEntry("lastURL", m_view->currentURL()); 
}

void ${APP_NAME}::readProperties(KConfig *config)
{
    // the 'config' object points to the session managed
    // config file.  this function is automatically called whenever
    // the app is being restored.  read in here whatever you wrote
    // in 'saveProperties'

    QString url = config->readEntry("lastURL"); 

    if (url != QString::null)
        m_view->openURL(url.ascii());
}

void ${APP_NAME}::dragEnterEvent(QDragEnterEvent *event)
{
    // accept uri drops only
    event->accept(QUriDrag::canDecode(event));
}

void ${APP_NAME}::dropEvent(QDropEvent *event)
{
    // this is a very simplistic implementation of a drop event.  we
    // will only accept a dropped URL.  the Qt dnd code can do *much*
    // much more, so please read the docs there
    QStrList uri;

    // see if we can decode a URI.. if not, just ignore it
    if (QUriDrag::decode(event, uri))
    {
        // okay, we have a URI.. process it
        QString url, target;
        url = uri.first();

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

    // this illustrates a simple use of KDialogBase.  all dialogs in
    // KDE should be derived from KDialogBase
    KDialogBase dialog;
    QLineEdit *url_edit = new QLineEdit(&dialog);
    dialog.setCaption(i18n("Enter a URL"));
    dialog.setMainWidget(url_edit);
    dialog.showButtonApply(false);
    if (dialog.exec())
        m_view->openURL(url_edit->text().ascii());
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
    KURL file_url = KFileDialog::getSaveURL();
    if (!file_url.isEmpty() && !file_url.isMalformed())
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
    if (QPrintDialog::getPrinterSetup(m_printer))
    {
        // setup the printer.  with Qt, you always "print" to a
        // QPainter.. whether the output medium is a pixmap, a screen,
        // or paper
        QPainter p;
        p.begin(m_printer);

        // we let our view do the actual printing
        QPaintDeviceMetrics metrics(m_printer);
        m_view->print(&p, metrics.height(), metrics.width());

        // and send the result to the printer
        p.end();
    }
}

void ${APP_NAME}::optionsShowToolbar()
{
    // this is all very cut and paste code for showing/hiding the
    // toolbar
    if (toolBar()->isVisible())
        toolBar()->enable(KToolBar::Hide);
    else
        toolBar()->enable(KToolBar::Show);
}

void ${APP_NAME}::optionsShowStatusbar()
{
    // this is all very cut and paste code for showing/hiding the
    // statusbar
    if (statusBar()->isVisible())
        statusBar()->enable(KStatusBar::Hide);
    else
        statusBar()->enable(KStatusBar::Show);
}

void ${APP_NAME}::optionsConfigure()
{
    KKeyDialog::configureKeys(m_accelKeys);
}

void ${APP_NAME}::optionsPreferences()
{
    // popup some sort of preference dialog, here
    ${APP_NAME}Preferences *dlg = new ${APP_NAME}Preferences;
    if (dlg->exec())
    {
        // redo your settings
    }
}

void ${APP_NAME}::changeStatusbar(const QString& text)
{
    // display the text on the statusbar
    statusBar()->message(text);
}

void ${APP_NAME}::changeCaption(const QString& text)
{
    // display the text on the caption
    setCaption(text);
}
