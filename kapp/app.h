echo "Creating $LOCATION_ROOT/$APP_NAME_LC/${APP_NAME_LC}.h...";
cat << EOF > $LOCATION_ROOT/$APP_NAME_LC/${APP_NAME_LC}.h
#ifndef ${APP_NAME_UC}_H
#define ${APP_NAME_UC}_H

#ifdef HAVE_CONFIG_H
#include <config.h>
#endif

#include <kapplication.h>
#include <kmainwindow.h>

#include "${APP_NAME_LC}view.h"

class KPrinter;
class KURL;

/**
 * This class serves as the main window for ${APP_NAME}.  It handles the
 * menus, toolbars, and status bars.
 *
 * @short Main window class
 * @author $AUTHOR <$EMAIL>
 * @version $APP_VERSION
 */
class ${APP_NAME} : public KMainWindow
{
    Q_OBJECT
public:
    /**
     * Default Constructor
     */
    ${APP_NAME}();

    /**
     * Default Destructor
     */
    virtual ~${APP_NAME}();

    /**
     * Use this method to load whatever file/URL you have
     */
    void load(const KURL& url);

protected:
    /**
     * Overridden virtuals for Qt drag 'n drop (XDND)
     */
    virtual void dragEnterEvent(QDragEnterEvent *event);
    virtual void dropEvent(QDropEvent *event);

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


private slots:
    void fileNew();
    void fileOpen();
    void fileSave();
    void fileSaveAs();
    void filePrint();
    void optionsConfigureToolbars();
    void optionsPreferences();
    void newToolbarConfig();

    void changeStatusbar(const QString& text);
    void changeCaption(const QString& text);

private:
    void setupAccel();
    void setupActions();

private:
    ${APP_NAME}View *m_view;

    KPrinter   *m_printer;
};

#endif // ${APP_NAME_UC}_H
