#ifndef %{APPNAMEUC}SHAPEFACTORY_H
#define %{APPNAMEUC}SHAPEFACTORY_H

#include <KoShapeFactory.h>
class KoShape;

class %{APPNAME}ShapeFactory : public KoShapeFactory
{
public:
	%{APPNAME}ShapeFactory(QObject *parent);
    
    KoShape *createDefaultShape() const;
    KoShape *createShape(const KoProperties *params) const;
};

#endif // %{APPNAME}ShapeFactory.h
