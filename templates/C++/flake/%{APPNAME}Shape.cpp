#include "%{APPNAME}Shape.h"

#include <KoShapeBackground.h>
#include <KoTextDocumentLayout.h>
#include <KoInlineTextObjectManager.h>
#include <KoDom.h>
#include <KoXmlWriter.h>
#include <KoShapeLoadingContext.h>
#include <KoShapeSavingContext.h>

#include <QPainter>

#include <KDebug>

%{APPNAME}Shape::%{APPNAME}Shape()
{
    setShapeId("%{APPNAME}Shape_ID");
    setCollisionDetection(true);
}

%{APPNAME}Shape::~%{APPNAME}Shape()
{
}

void %{APPNAME}Shape::paint(QPainter& painter, const KoViewConverter& converter)
{
    applyConversion(painter, converter);
    if(background())
    {
        QPainterPath p;
        p.addRect(QRectF(QPointF(), size()));
        background()->paint(painter, p);
    }
    
	// painting goes here
}

bool %{APPNAME}Shape::loadOdf( const KoXmlElement& element, KoShapeLoadingContext& context )
{
	kDebug() << "Loading %{APPNAME}Shape";
	
	loadOdfAttributes(element, context, OdfAllAttributes);
	
	KoXmlElement score = KoXml::namedItemNS(element, "http://www.koffice.org/%{APPNAMELC}", "score-partwise");
	
	// loading data goes here
	
	return true;
}

void %{APPNAME}Shape::saveOdf( KoShapeSavingContext& context ) const
{
	kDebug() << "Saving %{APPNAME}Shape";
	
	KoXmlWriter& writer = context.xmlWriter();
	writer.startElement("draw:frame");
	saveOdfAttributes(context, OdfAllAttributes);
	
	writer.startElement("%{APPNAMELC}:shape");
	writer.addAttribute("xmlns:%{APPNAMELC}", "http://www.koffice.org/%{APPNAMELC}");
	
	// saving data goes here
	
	writer.endElement(); // %{APPNAMELC}:shape
	
	saveOdfCommonChildElements(context);
	writer.endElement(); // draw:frame
}
