echo "Creating $LOCATION_ROOT/${APP_NAME_LC}/main.cpp...";
cat << EOF > $LOCATION_ROOT/${APP_NAME_LC}/main.cpp
#include "${APP_NAME_LC}.h"
#include <kapp.h>
#include <kaboutdata.h>
#include <kcmdlineargs.h>
#include <klocale.h>

static const char *description =
    I18N_NOOP("A KDE KPart Application");

static const char *version = "v${APP_VERSION}";

int main(int argc, char **argv)
{
    KAboutData about("${APP_NAME_LC}", I18N_NOOP("${APP_NAME}"), version, description, KAboutData::License_GPL, "(C) 2001 ${AUTHOR}", 0, 0, "${EMAIL}");
    about.addAuthor( "${AUTHOR}", 0, "${EMAIL}" );
    KCmdLineArgs::init(argc, argv, &about);
    KApplication app;

    // see if we are starting with session management
    if (app.isRestored())
        RESTORE(${APP_NAME})
    else
    {
        // no session.. just start up normally
        ${APP_NAME} *widget = new ${APP_NAME};
        if (argc > 1)
            widget->load(argv[1]);
        widget->show();
    }

    return app.exec();
}
