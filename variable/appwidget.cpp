echo "Creating $LOCATION_ROOT/$APP_NAME_LC/${APP_NAME_LC}widget.cpp...";
cat << EOF > $LOCATION_ROOT/$APP_NAME_LC/${APP_NAME_LC}widget.cpp
#include "${APP_NAME_LC}widget.h"

${APP_NAME}Widget::${APP_NAME}Widget(QWidget *parent, const char *name)
	: QWidget(parent, name)
{
}

${APP_NAME}Widget::~${APP_NAME}Widget()
{
}
