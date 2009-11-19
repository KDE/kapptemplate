#ifndef %{APPNAMEUC}TOOL_H
#define %{APPNAMEUC}TOOL_H

#include <KoTool.h>
class %{APPNAME}Shape;
class %{APPNAME}Widget;

class %{APPNAME}Tool : public KoTool
{
    Q_OBJECT
public:    
    %{APPNAME}Tool ( KoCanvasBase *canvas );
    void paint( QPainter& painter, const KoViewConverter& viewconverter );
    void mousePressEvent( KoPointerEvent* );
    void mouseMoveEvent( KoPointerEvent* );
    void mouseReleaseEvent( KoPointerEvent* );
    QWidget *createOptionWidget();
    void activate( bool temporary = false );
    void deactivate();
private:
    %{APPNAME}Shape *m_shape;
};

#endif // %{APPNAME}Tool.h
