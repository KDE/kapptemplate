/*
 * %{APPNAMELC}.cpp
 *
 * Copyright (C) 2004 $AUTHOR <$EMAIL>
 */
#include "%{APPNAMELC}.h"
#include "%{APPNAMELC}.moc"

#include <kaction.h>
#include <kactioncollection.h>
#include <kconfig.h>
#include <kedittoolbar.h>
#include <kfiledialog.h>
#include <kshortcutsdialog.h>
#include <klibloader.h>
#include <kmessagebox.h>
#include <kstandardaction.h>
#include <kstatusbar.h>
#include <kurl.h>
#include <klocale.h>

#include <QApplication>

%{APPNAME}::%{APPNAME}()
    : KParts::MainWindow( )
{
    // set the shell's ui resource file
    setXMLFile("%{APPNAMELC}_shell.rc");

    // then, setup our actions
    setupActions();

    // this routine will find and load our Part.  it finds the Part by
    // name which is a bad idea usually.. but it's alright in this
    // case since our Part is made for this Shell
    KLibFactory *factory = KLibLoader::self()->factory("lib%{APPNAMELC}part");
    if (factory)
    {
        // now that the Part is loaded, we cast it to a Part to get
        // our hands on it
        m_part = static_cast<KParts::ReadWritePart *>(factory->create(this,
                                "%{APPNAME}Part" ));

        if (m_part)
        {
            // tell the KParts::MainWindow that this is indeed the main widget
            setCentralWidget(m_part->widget());

            // and integrate the part's GUI with the shell's
            setupGUI();
        }
    }
    else
    {
        // if we couldn't find our Part, we exit since the Shell by
        // itself can't do anything useful
        KMessageBox::error(this, i18n("Could not find our Part!"));
        qApp->quit();
        // we return here, cause qApp->quit() only means "exit the
        // next time we enter the event loop...
        return;
    }

    // apply the saved mainwindow settings, if any, and ask the mainwindow
    // to automatically save settings if changed: window size, toolbar
    // position, icon size, etc.
    setAutoSaveSettings();
}

%{APPNAME}::~%{APPNAME}()
{
}

void %{APPNAME}::load(const KUrl& url)
{
    m_part->openUrl( url );
}

void %{APPNAME}::setupActions()
{
    KStandardAction::openNew(this, SLOT(fileNew()), actionCollection());
    KStandardAction::open(this, SLOT(fileOpen()), actionCollection());

    KStandardAction::quit(qApp, SLOT(closeAllWindows()), actionCollection());

    createStandardStatusBarAction();
    setStandardToolBarMenuEnabled(true);

    //KStandardAction::keyBindings(this, SLOT(optionsConfigureKeys()), actionCollection());
    //KStandardAction::configureToolbars(this, SLOT(optionsConfigureToolbars()), actionCollection());
}

void %{APPNAME}::saveProperties(KConfigGroup & /*config*/)
{
    // the 'config' object points to the session managed
    // config file.  anything you write here will be available
    // later when this app is restored
}

void %{APPNAME}::readProperties(const KConfigGroup & /*config*/)
{
    // the 'config' object points to the session managed
    // config file.  this function is automatically called whenever
    // the app is being restored.  read in here whatever you wrote
    // in 'saveProperties'
}

void %{APPNAME}::fileNew()
{
    // this slot is called whenever the File->New menu is selected,
    // the New shortcut is pressed (usually CTRL+N) or the New toolbar
    // button is clicked

    // About this function, the style guide (
    // http://developer.kde.org/documentation/standards/kde/style/basics/index.html )
    // says that it should open a new window if the document is _not_
    // in its initial state.  This is what we do here..
    if ( ! m_part->url().isEmpty() || m_part->isModified() )
    {
        (new %{APPNAME})->show();
    };
}

void %{APPNAME}::optionsConfigureKeys()
{
  /*KShortcutsDialog dlg( KKeyChooser::AllActions, KKeyChooser::LetterShortcutsDisallowed, this );
  dlg.insert( actionCollection(), "%{APPNAMELC}_shell.rc" );
  dlg.insert( m_part->actionCollection(), "%{APPNAMELC}_part.rc" );
  (void) dlg.configure( true );*/
}

void %{APPNAME}::optionsConfigureToolbars()
{
    //saveMainWindowSettings(KGlobal::config(), autoSaveGroup());

    // use the standard toolbar editor
    /*KEditToolBar dlg(factory());
    connect(&dlg, SIGNAL(newToolbarConfig()),
            this, SLOT(applyNewToolbarConfig()));
    dlg.exec();*/
}

void %{APPNAME}::applyNewToolbarConfig()
{
    //applyMainWindowSettings(KGlobal::config(), autoSaveGroup());
}

void %{APPNAME}::fileOpen()
{
    // this slot is called whenever the File->Open menu is selected,
    // the Open shortcut is pressed (usually CTRL+O) or the Open toolbar
    // button is clicked
    KUrl url =
        KFileDialog::getOpenUrl( KUrl(), QString(), this );

    if (url.isEmpty() == false)
    {
        // About this function, the style guide (
        // http://developer.kde.org/documentation/standards/kde/style/basics/index.html )
        // says that it should open a new window if the document is _not_
        // in its initial state.  This is what we do here..
        if ( m_part->url().isEmpty() && ! m_part->isModified() )
        {
            // we open the file in this window...
            load( url );
        }
        else
        {
            // we open the file in a new window...
            %{APPNAME}* newWin = new %{APPNAME};
            newWin->load( url );
            newWin->show();
        }
    }
}
