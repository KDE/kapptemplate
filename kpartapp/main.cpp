echo "Creating $LOCATION_ROOT/${APP_NAME_LC}/main.cpp...";
cat << EOF > $LOCATION_ROOT/${APP_NAME_LC}/main.cpp
#include "${APP_NAME_LC}.h"
#include <kapplication.h>
#include <kaboutdata.h>
#include <kcmdlineargs.h>
#include <klocale.h>

static const char description[] =
    I18N_NOOP("A KDE KPart Application");

static const char version[] = "v${APP_VERSION}";

static KCmdLineOptions options[] =
{
    { "+[URL]", I18N_NOOP( "Document to open" ), 0 },
    KCmdLineLastOption
};

int main(int argc, char **argv)
{
    KAboutData about("${APP_NAME_LC}", I18N_NOOP("${APP_NAME}"), version, description, KAboutData::License_GPL, "(C) 2004 ${AUTHOR}", 0, 0, "${EMAIL}");
    about.addAuthor( "${AUTHOR}", 0, "${EMAIL}" );
    KCmdLineArgs::init(argc, argv, &about);
    KCmdLineArgs::addCmdLineOptions( options );
    KApplication app;

    // see if we are starting with session management
    if (app.isRestored())
        RESTORE(${APP_NAME})
    else
    {
        // no session.. just start up normally
        KCmdLineArgs *args = KCmdLineArgs::parsedArgs();

        if ( args->count() == 0 )
        {
        ${APP_NAME} *widget = new ${APP_NAME};
        widget->show();
        }
        else
        {
            int i = 0;
            for (; i < args->count(); i++ )
            {
                ${APP_NAME} *widget = new ${APP_NAME};
                widget->show();
                widget->load( args->url( i ) );
            }
        }
        args->clear();
    }

    return app.exec();
}
