echo "Creating $LOCATION_ROOT/$APP_NAME_LC/plugin_${APP_NAME_LC}.cpp...";
cat << EOF > $LOCATION_ROOT/$APP_NAME_LC/plugin_${APP_NAME_LC}.cpp
#include "plugin_${APP_NAME_LC}.h"

#include <khtml_part.h>
#include <kaction.h>
#include <kinstance.h>
#include <kmessagebox.h>
#include <klocale.h>
#include <kgenericfactory.h>

typedef KGenericFactory<Plugin${APP_NAME}> ${APP_NAME}Factory;
K_EXPORT_COMPONENT_FACTORY( lib${APP_NAME_LC}plugin, 
                            ${APP_NAME}Factory( "${APP_NAME_LC}" ) );

Plugin${APP_NAME}::Plugin${APP_NAME}( QObject* parent, const char* name,
                                      const QStringList & /*args*/ )
    : Plugin( parent, name )
{
    // Instantiate all of your actions here.  These will appear in
    // Konqueror's menu and toolbars.
    (void) new KAction( i18n("&Plugin Action"), "${APP_NAME_LC}", 0,
                        this, SLOT(slotAction()),
                        actionCollection(), "plugin_action" );
}

Plugin${APP_NAME}::~Plugin${APP_NAME}()
{
}

void Plugin${APP_NAME}::slotAction()
{
    // This plugin assumes KHTMLPart.  If your plugin can handle more
    // than this or a different Part than this, simply delete or
    // change the following block.
    if ( !parent()->inherits("KHTMLPart") )
    {
        QString title( i18n( "Cannot Translate Source" ) );
        QString text( i18n( "You cannot translate anything except web pages "
                            "with this plugin." ) );

        KMessageBox::sorry( 0, text, title );
        return;
    }

    // Get a handle on our parent so we may get the necessary data for
    // processing
    KHTMLPart *part = dynamic_cast<KHTMLPart *>(parent());

    // This plugin only uses the URL.  You may use whatever data you
    // need.
    KURL url( part->url() );

    // This is a standard check to make sure we are dealing with a
    // valid URL
    if ( !url.isValid() )
    {
        QString title( i18n( "Malformed URL" ) );
        QString text( i18n( "The URL you entered is not valid, please "
                            "correct it and try again." ) );

        KMessageBox::sorry( 0, text, title );
        return;
    }

// The following block is very plugin specific.  In this example, we
// translate the current page with AltaVista's BabelFish.  You will
// definitely want to change this.
// BEGIN
    KURL work( "http://babel.altavista.com/translate.dyn" );

    QString query( "urltext=" );
    query += KURL::encode_string( url.url() );
    work.setQuery( query );
// END

    // Finally, execute the request
    part->openURL( work );
}

#include <plugin_${APP_NAME_LC}.moc>
