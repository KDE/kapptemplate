#ifndef %{APPNAMEUC}TOOLFACTORY_H
#define %{APPNAMEUC}TOOLFACTORY_H

#include <KoToolFactory.h>

class %{APPNAME}ToolFactory : public KoToolFactory
{
public:
	explicit %{APPNAME}ToolFactory(QObject *parent);
	
	KoTool * createTool(KoCanvasBase *canvas);
};

#endif // %{APPNAME}ToolFactory.h
