echo "Creating $LOCATION_ROOT/${APP_NAME_LC}/${APP_NAME_LC}.cpp...";
cat << EOF > $LOCATION_ROOT/${APP_NAME_LC}/${APP_NAME_LC}.cpp
/*
 * ${APP_NAME_LC}.cpp
 *
 * Copyright (C) 2004 $AUTHOR <$EMAIL>
 */
#include "${APP_NAME_LC}.h"
#include "${APP_NAME_LC}.moc"

#include <kkeydialog.h>
#include <kconfig.h>
#include <kurl.h>

#include <kedittoolbar.h>

#include <kaction.h>
#include <kstdaction.h>

#include <klibloader.h>
#include <kmessagebox.h>
#include <kfiledialog.h>
#include <kstatusbar.h>

${APP_NAME}::${APP_NAME}()
    : KParts::MainWindow( 0L, "${APP_NAME}" )
{
    // set the shell's ui resource file
    setXMLFile("${APP_NAME_LC}_shell.rc");

    // then, setup our actions
    setupActions();

    // this routine will find and load our Part.  it finds the Part by
    // name which is a bad idea usually.. but it's alright in this
    // case since our Part is made for this Shell
    KLibFactory *factory = KLibLoader::self()->factory("lib${APP_NAME_LC}part");
    if (factory)
    {
        // now that the Part is loaded, we cast it to a Part to get
        // our hands on it
        m_part = static_cast<KParts::ReadWritePart *>(factory->create(this,
                                "${APP_NAME_LC}_part", "KParts::ReadWritePart" ));

        if (m_part)
        {
            // tell the KParts::MainWindow that this is indeed the main widget
            setCentralWidget(m_part->widget());

            // and integrate the part's GUI with the shell's
            createGUI(m_part);
        }
    }
    else
    {
        // if we couldn't find our Part, we exit since the Shell by
        // itself can't do anything useful
        KMessageBox::error(this, "Could not find our Part!");
        kapp->quit();
        // we return here, cause kapp->quit() only means "exit the
        // next time we enter the event loop...
        return;
    }

    // apply the saved mainwindow settings, if any, and ask the mainwindow
    // to automatically save settings if changed: window size, toolbar
    // position, icon size, etc.
    setAutoSaveSettings();
}

${APP_NAME}::~${APP_NAME}()
{
}

void ${APP_NAME}::load(const KURL& url)
{
    m_part->openURL( url );
}

void ${APP_NAME}::setupActions()
{
    KStdAction::openNew(this, SLOT(fileNew()), actionCollection());
    KStdAction::open(this, SLOT(fileOpen()), actionCollection());

    KStdAction::quit(kapp, SLOT(quit()), actionCollection());

    createStandardStatusBarAction();
    setStandardToolBarMenuEnabled(true);

    KStdAction::keyBindings(this, SLOT(optionsConfigureKeys()), actionCollection());
    KStdAction::configureToolbars(this, SLOT(optionsConfigureToolbars()), actionCollection());
}

void ${APP_NAME}::saveProperties(KConfig* /*config*/)
{
    // the 'config' object points to the session managed
    // config file.  anything you write here will be available
    // later when this app is restored
}

void ${APP_NAME}::readProperties(KConfig* /*config*/)
{
    // the 'config' object points to the session managed
    // config file.  this function is automatically called whenever
    // the app is being restored.  read in here whatever you wrote
    // in 'saveProperties'
}

void ${APP_NAME}::fileNew()
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
        (new ${APP_NAME})->show();
    };
}

void ${APP_NAME}::optionsConfigureKeys()
{
  KKeyDialog dlg( true,  this );
  dlg.insert( actionCollection(), "${APP_NAME_LC}_shell.rc" );
  dlg.insert( m_part->actionCollection(), "${APP_NAME_LC}_part.rc" );
  (void) dlg.configure( true );
}

void ${APP_NAME}::optionsConfigureToolbars()
{
    saveMainWindowSettings(KGlobal::config(), autoSaveGroup());

    // use the standard toolbar editor
    KEditToolbar dlg(factory());
    connect(&dlg, SIGNAL(newToolbarConfig()),
            this, SLOT(applyNewToolbarConfig()));
    dlg.exec();
}

void ${APP_NAME}::applyNewToolbarConfig()
{
    applyMainWindowSettings(KGlobal::config(), autoSaveGroup());
}

void ${APP_NAME}::fileOpen()
{
    // this slot is called whenever the File->Open menu is selected,
    // the Open shortcut is pressed (usually CTRL+O) or the Open toolbar
    // button is clicked
    KURL url =
        KFileDialog::getOpenURL( QString::null, QString::null, this );

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
            ${APP_NAME}* newWin = new ${APP_NAME};
            newWin->load( url );
            newWin->show();
        }
    }
}
