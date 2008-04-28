#ifndef %{APPNAMEUC}_H
#define %{APPNAMEUC}_H

#include <kparts/mainwindow.h>

/**
 * This is the application "Shell".  It has a menubar, toolbar, and
 * statusbar but relies on the "Part" to do all the real work.
 *
 * @short Application Shell
 * @author ${AUTHOR} <${EMAIL}>
 * @version ${APP_VERSION}
 */
class %{APPNAME} : public KParts::MainWindow
{
    Q_OBJECT
public:
    /**
     * Default Constructor
     */
    %{APPNAME}();

    /**
     * Default Destructor
     */
    virtual ~%{APPNAME}();

    /**
     * Use this method to load whatever file/URL you have
     */
    void load(const KUrl& url);

protected:
    /**
     * This method is called when it is time for the app to save its
     * properties for session management purposes.
     */
    void saveProperties(KConfigGroup &);

    /**
     * This method is called when this app is restored.  The KConfig
     * object points to the session management config file that was saved
     * with @ref saveProperties
     */
    void readProperties(const KConfigGroup &);

private slots:
    void fileNew();
    void fileOpen();
    void optionsConfigureKeys();
    void optionsConfigureToolbars();

    void applyNewToolbarConfig();

private:
    void setupActions();

private:
    KParts::ReadWritePart *m_part;
};

#endif // %{APPNAMEUC}_H
