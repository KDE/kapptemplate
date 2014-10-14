#include "%{APPNAME}ToolFactory.h"
#include "%{APPNAME}Tool.h"

%{APPNAME}ToolFactory::%{APPNAME}ToolFactory( QObject* parent ) : KoToolFactory ( parent, "%{APPNAME}ToolFactory_ID", i18n("%{APPNAME} tool") )
{
    setToolTip( i18n( "%{APPNAME} - Tooltip" ) );
    setIcon( i18n( "kword" ) );
    setToolType( dynamicToolType() );
    setPriority( 2 );
    setActivationShapeId( "%{APPNAME}Shape_ID" );
}

KoTool *%{APPNAME}ToolFactory::createTool( KoCanvasBase *canvas )
{
    return new %{APPNAME}Tool(canvas);
}
