echo "Creating $LOCATION_ROOT/$APP_NAME_LC/${APP_NAME_LC}.h...";
cat << EOF > $LOCATION_ROOT/$APP_NAME_LC/${APP_NAME_LC}.h
#ifndef ${APP_NAME_UC}_H
#define ${APP_NAME_UC}_H

#ifdef HAVE_CONFIG_H
#include <config.h>
#endif 

#include <kapp.h>
#include <kparts/mainwindow.h>
 
class KToggleAction;

/**
 * This is the application "Shell".  It has a menubar, toolbar, and
 * statusbar but relies on the "Part" to do all the real work.
 *
 * @short Application Shell
 * @author ${AUTHOR} <${EMAIL}>
 * @version ${APP_VERSION}
 */
class ${APP_NAME} : public KParts::MainWindow
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
     * This method is called when it is time for the app to save its
     * properties for session management purposes.
     */
    void saveProperties(KConfig *);

    /**
     * This method is called when this app is restored.  The KConfig
     * object points to the session management config file that was saved
     * with @ref saveProperties
     */
    void readProperties(KConfig *);

private slots:
    void fileNew();
    void optionsShowToolbar();
    void optionsShowStatusbar();
    void optionsConfigureKeys();
    void optionsConfigureToolbars();

private:
    void setupAccel();
    void setupActions();

private:
    KParts::ReadWritePart *m_part;

    KToggleAction *m_toolbarAction;
    KToggleAction *m_statusbarAction;
};

#endif // ${APP_NAME_UC}_H
