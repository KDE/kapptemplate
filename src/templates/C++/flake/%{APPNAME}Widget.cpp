#include "%{APPNAME}Widget.h"
#include "%{APPNAME}Shape.h"

#include <KDebug>

%{APPNAME}Widget::%{APPNAME}Widget(%{APPNAME}Shape *shape, QWidget *parent) : QWidget(parent), m_shape(shape)
{
}
