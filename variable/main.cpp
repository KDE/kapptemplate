echo "Creating $LOCATION_ROOT/$APP_NAME_LC/main.cpp...";
cat << EOF > $LOCATION_ROOT/$APP_NAME_LC/main.cpp
#include "$APP_NAME_LC.h"
#include <kapp.h>

int main(int argc, char *argv[])
{
	KApplication app(argc, argv, "$APP_NAME_LC");

	// All session management is handled in the RESTORE macro
	if (app.isRestored())
	{
		RESTORE($APP_NAME)
	}
	else
	{
		$APP_NAME *widget = new $APP_NAME;
		widget->show();
	}

	return app.exec();
}
