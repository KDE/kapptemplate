echo "Creating $LOCATION_ROOT/$APP_NAME_LC/$APP_NAME_LC.h...";
cat << EOF > $LOCATION_ROOT/$APP_NAME_LC/$APP_NAME_LC.h
#ifndef ${APP_NAME_UC}_H 
#define ${APP_NAME_UC}_H 

#ifdef HAVE_CONFIG_H
#include <config.h>
#endif 

#include <kapp.h>
#include <ktmainwindow.h>
 
#include "${APP_NAME_LC}widget.h"

/**
 * This class serves as the main window for $APP_NAME.  It handles the
 * menus, toolbars, and status bars.
 *
 * @short Main window class
 * @author $AUTHOR <$EMAIL>
 * @version $APP_VERSION
 */
class $APP_NAME : public KTMainWindow
{
	Q_OBJECT
public:
	/**
	 * Default Constructor
	 */
	$APP_NAME();

	/**
	 * Default Destructor
	 */
	virtual ~$APP_NAME();

public slots:
	/**
	 * This is called whenever the user Drag n' Drops something into our
	 * window
	 */
	void slotDropEvent(KDNDDropZone *);
 
protected:
	/**
	 * This function is called when it is time for the app to save its
	 * properties for session management purposes.
	 */
	void saveProperties(KConfig *);

	/**
	 * This function is called when this app is restored.  The KConfig
	 * object points to the session management config file that was saved
	 * with @ref saveProperties
	 */
	void readProperties(KConfig *);

private:
	${APP_NAME}Widget *view;
};

#endif // ${APP_NAME_UC}_H 
