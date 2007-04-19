echo "Creating $LOCATION_ROOT/main.cpp...";
cat << EOF > $LOCATION_ROOT/main.cpp
#include "${APP_NAME_LC}.h"
#include <kapplication.h>
#include <kaboutdata.h>
#include <kcmdlineargs.h>
#include <klocale.h>

static const char description[] =
    I18N_NOOP("A KDE 4 Application");

static const char version[] = "${APP_VERSION}";

static KCmdLineOptions options[] =
{
    { "+[URL]", I18N_NOOP( "Document to open" ), 0 },
    KCmdLineLastOption
};

int main(int argc, char **argv)
{
    KAboutData about("${APP_NAME_LC}", I18N_NOOP("${APP_NAME}"), version, description,
                     KAboutData::License_GPL, "(C) 2007 ${AUTHOR}", 0, 0, "${EMAIL}");
    about.addAuthor( "${AUTHOR}", 0, "${EMAIL}" );
    KCmdLineArgs::init(argc, argv, &about);
    KCmdLineArgs::addCmdLineOptions(options);
    KApplication app;

    ${APP_NAME} *widget = new ${APP_NAME};

    // see if we are starting with session management
    if (app.isSessionRestored())
    {
        RESTORE(${APP_NAME});
    }
    else
    {
        // no session.. just start up normally
        KCmdLineArgs *args = KCmdLineArgs::parsedArgs();
        if (args->count() == 0)
        {
            //${APP_NAME_LC} *widget = new ${APP_NAME_LC};
            widget->show();
        }
        else
        {
            int i = 0;
            for (; i < args->count(); i++)
            {
                //${APP_NAME_LC} *widget = new ${APP_NAME_LC};
                widget->show();
            }
        }
        args->clear();
    }

    return app.exec();
}
