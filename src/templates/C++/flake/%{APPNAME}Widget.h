#ifndef %{APPNAMEUC}WIDGET_H
#define %{APPNAMEUC}WIDGET_H

#include <QWidget>

class %{APPNAME}Shape;

class %{APPNAME}Widget : public QWidget
{
    Q_OBJECT
public:
    %{APPNAME}Widget(%{APPNAME}Shape *shape, QWidget *parent = 0);
	
private:
	%{APPNAME}Shape *m_shape;
};

#endif // %{APPNAME}Widget.h
