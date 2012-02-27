#include "%{APPNAME}Plugin.h"
#include <KoShapeRegistry.h>
#include <KoToolRegistry.h>
#include "%{APPNAME}ShapeFactory.h"
#include "%{APPNAME}ToolFactory.h"
#include <KPluginFactory>

K_PLUGIN_FACTORY(%{APPNAME}PluginFactory, registerPlugin<%{APPNAME}Plugin>(); )
K_EXPORT_PLUGIN(%{APPNAME}PluginFactory("%{APPNAME}"))

%{APPNAME}Plugin::%{APPNAME}Plugin(QObject *parent, const QVariantList&) : QObject(parent)
{
    KoShapeRegistry::instance()->add(new %{APPNAME}ShapeFactory(parent));
    KoToolRegistry::instance()->add(new %{APPNAME}ToolFactory(parent));
}
