echo "Creating $LOCATION_ROOT/${APP_NAME_LC}/${APP_NAME_LC}widget.h...";
cat << EOF > $LOCATION_ROOT/${APP_NAME_LC}/${APP_NAME_LC}widget.h
#ifndef ${APP_NAME_UC}WIDGET_H 
#define ${APP_NAME_UC}WIDGET_H 

#ifdef HAVE_CONFIG_H
#include <config.h>
#endif 

#include <qwidget.h>

/**
 * This class is the main view for $APP_NAME.  Most non-menu, non-toolbar,
 * and non-status bar GUI code should go here.
 *
 * @short Main view
 * @author $AUTHOR <$EMAIL>
 * @version $APP_VERSION
 */
class ${APP_NAME}Widget : public QWidget
{
	Q_OBJECT
public:
	/**
	 * Default constructor
	 */
	${APP_NAME}Widget(QWidget *parent = 0, const char *name = 0);

	/**
	 * Destructor
	 */
	virtual ~${APP_NAME}Widget();
};

#endif // ${APP_NAME_UC}WIDGET_H 
