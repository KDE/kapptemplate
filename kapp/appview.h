echo "Creating $LOCATION_ROOT/$APP_NAME_LC/${APP_NAME_LC}view.h...";
cat << EOF > $LOCATION_ROOT/$APP_NAME_LC/${APP_NAME_LC}view.h
#ifndef ${APP_NAME_UC}VIEW_H
#define ${APP_NAME_UC}VIEW_H

#include <qwidget.h>
#include <kparts/part.h>
#include <${APP_NAME_LC}iface.h>

class QPainter;
class KURL;

/**
 * This is the main view class for ${APP_NAME}.  Most of the non-menu,
 * non-toolbar, and non-statusbar (e.g., non frame) GUI code should go
 * here.
 *
 * This ${APP_NAME_LC} uses an HTML component as an example.
 *
 * @short Main view
 * @author $AUTHOR <$EMAIL>
 * @version $APP_VERSION
 */
class ${APP_NAME}View : public QWidget, public ${APP_NAME}Iface
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

    /**
     * Random 'get' function
     */
    QString currentURL();

    /**
     * Random 'set' function accessed by DCOP
     */
    virtual void openURL(QString url);

    /**
     * Random 'set' function
     */
    virtual void openURL(const KURL& url);

    /**
     * Print this view to any medium -- paper or not
     */
    void print(QPainter *, int height, int width);

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
    void slotOnURL(const QString& url);
    void slotSetTitle(const QString& title);

private:
    KParts::ReadOnlyPart *m_html;
};

#endif // ${APP_NAME_UC}VIEW_H
