echo "Creating $LOCATION_ROOT/${APP_NAME_LC}/${APP_NAME_LC}.cpp...";
cat << EOF > $LOCATION_ROOT/${APP_NAME_LC}/${APP_NAME_LC}.cpp
/*
 * ${APP_NAME_LC}.cpp
 *
 * Copyright (C) 1999 $AUTHOR <$EMAIL>
 */
#include "${APP_NAME_LC}.h"

#include <qkeycode.h>

#include <kfm.h>
#include <kiconloader.h>

${APP_NAME}::${APP_NAME}()
	: view(new ${APP_NAME}Widget(this))
{
	// tell the KTMainWindow that this is indeed the main widget
	setView(view);

	// create a DropZone over the entire window and connect it
	// to the slotDropEvent
	connect(new KDNDDropZone(this, DndURL), 
	        SIGNAL(dropAction(KDNDDropZone *)), 
	        SLOT(slotDropEvent(KDNDDropZone *)));


	// create a popup menu -- in this case, the File menu
	QPopupMenu* p = new QPopupMenu;
	p->insertItem(i18n("&Quit"), kapp, SLOT(quit()), CTRL+Key_Q);

	// put our newly created menu into the main menu bar
	menuBar()->insertItem(i18n("&File"), p);
	menuBar()->insertSeparator();

	// KDE will generate a short help menu automagically
	p = kapp->getHelpMenu(true, 
			 i18n("${APP_NAME} --- Short Description\n\n"
					"(c) 1999 $AUTHOR \n"
					"Long Description"));
	menuBar()->insertItem(i18n("&Help"), p);

	// insert a quit button.  the icon is the standard one in KDE
	toolBar()->insertButton(Icon("exit.xpm"),   // icon
	                        0,                  // button id
									SIGNAL(clicked()),  // action
									kapp, SLOT(quit()), // result
									i18n("Exit"));      // tooltip text

	// we do want a status bar
	enableStatusBar();
}

${APP_NAME}::~${APP_NAME}()
{
}

void ${APP_NAME}::slotDropEvent(KDNDDropZone *zone)
{
	// the user dropped something on our window.
	QString url, temp_file;

	// get the URL pointing to the dropped file
	url = zone->getURLList().first();

	// let KFM grab the file
	if (KFM::download(url, temp_file))
	{
		// 'temp_file' now contains the absolute path to a temp file
		// with the contents of the the dropped file.  You would presumably
		// handle it right now.

		// after you are done handling it, let KFM delete the temp file
		KFM::removeTempFile(temp_file);
	}
}

void ${APP_NAME}::saveProperties(KConfig *config)
{
	// the 'config' object points to the session managed
	// config file.  anything you write here will be available
	// later when this app is restored
	
	// e.g., config->writeEntry("key", var); 
}

void ${APP_NAME}::readProperties(KConfig *config)
{
	// the 'config' object points to the session managed
	// config file.  this function is automatically called whenever
	// the app is being restored.  read in here whatever you wrote
	// in 'saveProperties'

	// e.g., var = config->readEntry("key"); 
}
