echo "Creating $LOCATION_ROOT/src/${APP_NAME_LC}.h...";
cat << EOF > $LOCATION_ROOT/src/${APP_NAME_LC}.h
#ifndef ${APP_NAME_UC}_H
#define ${APP_NAME_UC}_H

#include <kxmlguiwindow.h>

#include <QDragEnterEvent>
#include <QDropEvent>

class ${APP_NAME}View;
class QPrinter;
class KUrl;

/**
 * This class serves as the main window for ${APP_NAME}.  It handles the
 * menus, toolbars, and status bars.
 *
 * @short Main window class
 * @author $AUTHOR <$EMAIL>
 * @version $APP_VERSION
 */
class ${APP_NAME} : public KXmlGuiWindow
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
    void load(const KUrl& url);

public Q_SLOTS:
    // DBus interface
    Q_SCRIPTABLE void fileOpen();
    Q_SCRIPTABLE void changeStatusbar(const QString &);

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
    void saveProperties(KConfigGroup &);

    /**
     * This function is called when this app is restored.  The KConfig
     * object points to the session management config file that was saved
     * with @ref saveProperties
     */
    void readProperties(const KConfigGroup &);


private slots:
    void fileNew();
    void fileSave();
    void fileSaveAs();
    void filePrint();
    void optionsPreferences();

    void changeCaption(const QString& text);

private:
    void setupActions();

private:
    ${APP_NAME}View *m_view;

    QPrinter   *m_printer;
};

#endif // ${APP_NAME_UC}_H