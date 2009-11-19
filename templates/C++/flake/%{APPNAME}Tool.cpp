#include "%{APPNAME}Tool.h"
#include "%{APPNAME}Shape.h"
#include "%{APPNAME}Widget.h"
#include <KoSelection.h>
#include <KoCanvasBase.h>
#include <KoShapeManager.h>
#include <KDebug>

%{APPNAME}Tool::%{APPNAME}Tool(KoCanvasBase *canvas) : KoTool(canvas), m_shape(0)
{
}

void %{APPNAME}Tool::paint(QPainter& painter, const KoViewConverter& viewConverter)
{
    Q_UNUSED(painter);
    Q_UNUSED(viewConverter);
}

void %{APPNAME}Tool::mousePressEvent(KoPointerEvent *event)
{
	Q_UNUSED(event);
}

void %{APPNAME}Tool::mouseMoveEvent(KoPointerEvent *event)
{
	Q_UNUSED(event);
}

void %{APPNAME}Tool::mouseReleaseEvent(KoPointerEvent *event)
{
	Q_UNUSED(event);
}

QWidget* %{APPNAME}Tool::createOptionWidget()
{
    return new %{APPNAME}Widget(m_shape);
}

void %{APPNAME}Tool::activate(bool temporary)
{
    Q_UNUSED( temporary );
    m_shape = 0;
    KoSelection *selection = m_canvas->shapeManager()->selection();
    foreach ( KoShape* shape, selection->selectedShapes() )
    {
        m_shape = dynamic_cast<%{APPNAME}Shape*>( shape );
        if ( m_shape )
            break;
    }
    if ( !m_shape )
    {
        emit done();
        return;
    }
    useCursor( Qt::ArrowCursor, true );
}

void %{APPNAME}Tool::deactivate()
{
    m_shape = 0;
}
