#ifndef %{APPNAMEUC}SHAPE_H
#define %{APPNAMEUC}SHAPE_H

#include <KoShape.h>

class %{APPNAME}Shape : public KoShape
{
public:
    %{APPNAME}Shape();
    ~%{APPNAME}Shape();
	
    void paint( QPainter &painter, const KoViewConverter &converter );
    bool loadOdf(const KoXmlElement & element, KoShapeLoadingContext &context);
    void saveOdf(KoShapeSavingContext & context) const;
};

#endif // %{APPNAME}Shape.h
