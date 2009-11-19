#include "%{APPNAME}ShapeFactory.h"
#include "%{APPNAME}Shape.h"

%{APPNAME}ShapeFactory::%{APPNAME}ShapeFactory (QObject* parent) : KoShapeFactory (parent, "%{APPNAME}Shape_ID", "%{APPNAME} - short description")
{
	
}

KoShape *%{APPNAME}ShapeFactory::createDefaultShape() const
{
	return new %{APPNAME}Shape;
}

KoShape *%{APPNAME}ShapeFactory::createShape (const KoProperties* params) const
{
    Q_UNUSED(params);
	return new %{APPNAME}Shape;
}
