echo "Creating $LOCATION_ROOT/${APP_NAME_LC}/${APP_NAME_LC}.cpp...";
cat << EOF > $LOCATION_ROOT/${APP_NAME_LC}/${APP_NAME_LC}.cpp
/*
 * ${APP_NAME_LC}.cpp
 *
 * Copyright (C) 1999 $AUTHOR <$EMAIL>
 */
#include "${APP_NAME_LC}.h"

#include "${APP_NAME_LC}pref.h"

#include <qpopupmenu.h>
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
#include <ktoolbar.h>
#include <kio_netaccess.h>
#include <kfiledialog.h>
#include <kconfig.h>

#include <kdialogbase.h>
#include <khelpmenu.h>

${APP_NAME}::${APP_NAME}()
    : m_view(new ${APP_NAME}View(this)),
      m_accelKeys(new KAccel(this))
{
    // accept dnd
    setAcceptDrops(true);

    // tell the KTMainWindow that this is indeed the main widget
    setView(m_view);

    // setup our menubars and toolbars
    setupMenuBars();
    setupToolBars();

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
    delete m_file;
    delete m_options;
    delete m_help;
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

void ${APP_NAME}::setupMenuBars()
{
    // these are the standard menus.  delete the ones that you
    // aren't using
    m_file    = new QPopupMenu();
    m_options = new QPopupMenu();
    m_help    = new QPopupMenu();

    // the first thing we need to do is setup our keyboard "shortcuts"
    // this uses the KAccel class -- it's similar to the old KStdAccel
    // only a LOT more powerful.
    
    // connect all of our standard accelerators to their slots
    m_accelKeys->connectItem(KAccel::New,   this, SLOT(fileNew()));
    m_accelKeys->connectItem(KAccel::Open,  this, SLOT(fileOpen()));
    m_accelKeys->connectItem(KAccel::Save,  this, SLOT(fileSave()));
    m_accelKeys->connectItem(KAccel::Print, this, SLOT(filePrint()));
    m_accelKeys->connectItem(KAccel::Quit,  kapp, SLOT(quit()));

    // we need to read in the default settings now.  if we do it
    // before the 'connectItem' calls or aver the 'changeMenuAccel'
    // calls, the settings will have no effect!
    m_accelKeys->readSettings();

    // first, the File menu
    int id;
    id = m_file->insertItem(BarIcon("filenew"), i18n("&New"),
                            this, SLOT(fileNew()));
    m_accelKeys->changeMenuAccel(m_file, id, KAccel::New);
    id = m_file->insertItem(BarIcon("fileopen"), i18n("&Open..."),
                            this, SLOT(fileOpen()));
    m_accelKeys->changeMenuAccel(m_file, id, KAccel::Open);
    m_file->insertSeparator(-1);

    id = m_file->insertItem(BarIcon("filefloppy"), i18n("&Save"),
                            this, SLOT(fileSave()));
    m_accelKeys->changeMenuAccel(m_file, id, KAccel::Save);
    m_file->insertItem(i18n("Save As..."),
                       this, SLOT(fileSaveAs()));
    m_file->insertSeparator(-1);

    id = m_file->insertItem(BarIcon("fileprint"), i18n("&Print"),
                            this, SLOT(filePrint()));
    m_accelKeys->changeMenuAccel(m_file, id, KAccel::Print);
    m_file->insertSeparator(-1);

    id = m_file->insertItem(BarIcon("exit"), i18n("&Quit"),
                            kapp, SLOT(quit()));
    m_accelKeys->changeMenuAccel(m_file, id, KAccel::Quit);

    // next, the Options menu
    m_options->setCheckable(true);
    m_toolbarId = m_options->insertItem(i18n("Show &Toolbar"),
                                        this, SLOT(optionsShowToolbar()));
    m_options->setItemChecked(m_toolbarId, true);
    m_statusbarId = m_options->insertItem(i18n("Show &Statusbar"),
                                          this, SLOT(optionsShowStatusbar()));
    m_options->setItemChecked(m_statusbarId, true);
    m_options->insertSeparator(-1);

    m_options->insertItem(i18n("Configure &Key Bindings..."),
                          this, SLOT(optionsConfigure()));
    m_options->insertItem(i18n("&Preferences..."),
                          this, SLOT(optionsPreferences()));

    // finally, the Help menu
    m_help = helpMenu(i18n("${APP_NAME} v${APP_VERSION}\\n\\n"
                           "Copyright (C) 1999\\n"
                           "$AUTHOR <$EMAIL>"));

    // now add all of the menus to the menu bar
    menuBar()->insertItem(i18n("&File"),    m_file);
    menuBar()->insertItem(i18n("&Options"), m_options);
    menuBar()->insertItem(i18n("&Help"),    m_help);
}

void ${APP_NAME}::setupToolBars()
{
    // this toolbar should mirror the menubar fairly closely

    toolBar()->insertButton(BarIcon("filenew"), -1, SIGNAL(clicked()),
                            this, SLOT(fileNew()), true, i18n("New"));
    toolBar()->insertButton(BarIcon("fileopen"), -1, SIGNAL(clicked()),
                            this, SLOT(fileOpen()), true, i18n("Open"));
    toolBar()->insertButton(BarIcon("filefloppy"), -1, SIGNAL(clicked()),
                            this, SLOT(fileSave()), true, i18n("Save"));
    toolBar()->insertButton(BarIcon("fileprint"), -1, SIGNAL(clicked()),
                            this, SLOT(filePrint()), true, i18n("Print"));
    KHelpMenu *help = new KHelpMenu(this);
    toolBar()->insertButton(BarIcon("help"), -1, SIGNAL(clicked()),
                            help, SLOT(appHelpActivated()),
                            true, i18n("Help"));

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

    QString file_name;
    if ((file_name = KFileDialog::getSaveFileName()) != QString::null)
    {
        // save your info, here
    }
}

void ${APP_NAME}::filePrint()
{
    // this slot is called whenever the File->Print menu is selected,
    // the Print shortcut is pressed (usually CTRL+P) or the Print toolbar
    // button is clicked

    QPrinter *printer = new QPrinter;
    if (QPrintDialog::getPrinterSetup(printer))
    {
        // setup the printer.  with Qt, you always "print" to a
        // QPainter.. whether the output medium is a pixmap, a screen,
        // or paper
        QPainter p;
        p.begin(printer);

        // we let our view do the actual printing
        QPaintDeviceMetrics metrics(printer);
        m_view->print(&p, metrics.height(), metrics.width());

        // and send the result to the printer
        p.end();
    }
}

void ${APP_NAME}::optionsShowToolbar()
{
    // this is all very cut and paste code for showing/hiding the
    // toolbar
    static bool show = true;
    show = show ? false : true;

    m_options->setItemChecked(m_toolbarId, show);

    if (show)
        toolBar()->enable(KToolBar::Show);
    else
        toolBar()->enable(KToolBar::Hide);
}

void ${APP_NAME}::optionsShowStatusbar()
{
    // this is all very cut and paste code for showing/hiding the
    // statusbar
    static bool show = true;
    show = show ? false : true;

    m_options->setItemChecked(m_statusbarId, show);

    if (show)
        statusBar()->enable(KStatusBar::Show);
    else
        statusBar()->enable(KStatusBar::Hide);
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
