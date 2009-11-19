#include "%{APPNAME}Plugin.h"
#include <KoShapeRegistry.h>
#include <KoToolRegistry.h>
#include "%{APPNAME}ShapeFactory.h"
#include "%{APPNAME}ToolFactory.h"
#include <KGenericFactory>

K_EXPORT_COMPONENT_FACTORY(%{APPNAMELC}shape,
                           KGenericFactory<%{APPNAME}Plugin>( "%{APPNAME}" ) )

%{APPNAME}Plugin::%{APPNAME}Plugin(QObject *parent, const QStringList&) : QObject(parent)
{
    KoShapeRegistry::instance()->add(new %{APPNAME}ShapeFactory(parent));
    KoToolRegistry::instance()->add(new %{APPNAME}ToolFactory(parent));
}
