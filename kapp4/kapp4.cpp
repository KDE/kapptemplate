echo "Creating $LOCATION_ROOT/${APP_NAME_LC}.cpp...";
cat << EOF > $LOCATION_ROOT/${APP_NAME_LC}.cpp
/*
 * ${APP_NAME_LC}.cpp
 *
 * Copyright (C) 2006 $AUTHOR <$EMAIL>
 */
#include "${APP_NAME_LC}.h"
#include "settings.h"

#include <QDropEvent>
#include <QPainter>

#include <kconfigdialog.h>
#include <kglobal.h>
#include <klocale.h>
#include <kicon.h>
#include <kprinter.h>
#include <kstatusbar.h>
#include <kkeydialog.h>

#include <kedittoolbar.h>

#include <kstdaccel.h>
#include <kaction.h>
#include <kstdaction.h>

${APP_NAME}::${APP_NAME}()
    : KMainWindow(),
      m_view(new ${APP_NAME}View(this)),
      m_printer(0)
{
    // accept dnd
    setAcceptDrops(true);

    // tell the KMainWindow that this is indeed the main widget
    setCentralWidget(m_view);

    // then, setup our actions
    setupActions();

    // and a status bar
    statusBar()->show();

    // apply the saved mainwindow settings, if any, and ask the mainwindow
    // to automatically save settings if changed: window size, toolbar
    // position, icon size, etc.
    setAutoSaveSettings();
}

${APP_NAME}::~${APP_NAME}()
{
}

void ${APP_NAME}::setupActions()
{
    KStdAction::openNew(this, SLOT(fileNew()), actionCollection());
    KStdAction::quit(kapp, SLOT(quit()), actionCollection());

    KStdAction::preferences(this, SLOT(optionsPreferences()), actionCollection());

    // custom menu and menu item - the slot is in the class ${APP_NAME}View
    KAction *custom = new KAction(i18n("Swi&tch Colors"), actionCollection(), "switch_action");
    custom->setIcon(KIcon("colorize"));
    connect(custom, SIGNAL(triggered(bool)), m_view, SLOT(switchColors()));
    setupGUI();
}

void ${APP_NAME}::fileNew()
{
    // this slot is called whenever the File->New menu is selected,
    // the New shortcut is pressed (usually CTRL+N) or the New toolbar
    // button is clicked

    // create a new window
    (new ${APP_NAME})->show();
}

void ${APP_NAME}::optionsPreferences()
{
	// The preference dialog is derived from prefs_base.ui 
	//
	// compare the names of the widgets in the .ui file 
	// to the names of the variables in the .kcfg file
        KConfigDialog *dialog = new KConfigDialog(this, "settings", Settings::self());
    	QWidget *generalSettingsDlg = new QWidget;
    	ui_prefs_base.setupUi(generalSettingsDlg);
    	dialog->addPage(generalSettingsDlg, i18n("General"), "package_setting");
        connect(dialog, SIGNAL(settingsChanged(const QString &)), m_view, SLOT(settingsChanged()));
        dialog->show();
}

#include "${APP_NAME_LC}.moc"

