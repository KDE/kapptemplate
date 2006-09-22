echo "Creating $LOCATION_ROOT/${APP_NAME_LC}view.h...";
cat << EOF > $LOCATION_ROOT/${APP_NAME_LC}view.h

#ifndef _${APP_NAME_UC}VIEW_H_
#define _${APP_NAME_UC}VIEW_H_

#include <QWidget>

#include "ui_${APP_NAME_LC}view_base.h"

class QPainter;
class KURL;

/**
 * This is the main view class for %{APPNAME}.  Most of the non-menu,
 * non-toolbar, and non-statusbar (e.g., non frame) GUI code should go
 * here.
 *
 * @short Main view
 * @author %{AUTHOR} <%{EMAIL}>
 * @version %{VERSION}
 */

class ${APP_NAME}View : public QWidget, public Ui::${APP_NAME_LC}view_base
{
    Q_OBJECT
public:
	/**
	 * Default constructor
	 */
    ${APP_NAME}View(QWidget *parent);

	/**
	 * Destructor
	 */
    virtual ~${APP_NAME}View();

private:
    Ui::${APP_NAME_LC}view_base ui_${APP_NAME_LC}view_base;

signals:
    /**
     * Use this signal to change the content of the statusbar
     */
    void signalChangeStatusbar(const QString& text);

    /**
     * Use this signal to change the content of the caption
     */
    void signalChangeCaption(const QString& text);

private slots:
    void switchColors();
    void settingsChanged();
};

#endif // _${APP_NAME}VIEW_H_
