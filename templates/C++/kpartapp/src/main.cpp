#include "%{APPNAMELC}.h"
#include <kapplication.h>
#include <kaboutdata.h>
#include <kcmdlineargs.h>
#include <klocale.h>

static const char description[] =
    I18N_NOOP("A KDE KPart Application");

static const char version[] = "%{VERSION}";

int main(int argc, char **argv)
{
    KAboutData about("%{APPNAMELC}", 0, ki18n("%{APPNAME}"), version, ki18n(description), KAboutData::License_GPL, ki18n("(C) 2008 %{AUTHOR}"), KLocalizedString(), 0, "%{EMAIL}");
    about.addAuthor( ki18n("%{AUTHOR}"), KLocalizedString(), "%{EMAIL}" );
    KCmdLineArgs::init(argc, argv, &about);

    KCmdLineOptions options;
    options.add("+[URL]", ki18n( "Document to open" ));
    KCmdLineArgs::addCmdLineOptions( options );
    KApplication app;

    // see if we are starting with session management
    if (app.isSessionRestored())
        RESTORE(%{APPNAME})
    else
    {
        // no session.. just start up normally
        KCmdLineArgs *args = KCmdLineArgs::parsedArgs();

        if ( args->count() == 0 )
        {
        %{APPNAME} *widget = new %{APPNAME};
        widget->show();
        }
        else
        {
            int i = 0;
            for (; i < args->count(); i++ )
            {
                %{APPNAME} *widget = new %{APPNAME};
                widget->show();
                widget->load( args->url( i ) );
            }
        }
        args->clear();
    }

    return app.exec();
}
