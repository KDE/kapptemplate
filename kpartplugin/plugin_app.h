echo "Creating $LOCATION_ROOT/$APP_NAME_LC/plugin_${APP_NAME_LC}.h...";
cat << EOF > $LOCATION_ROOT/$APP_NAME_LC/plugin_${APP_NAME_LC}.h
#ifndef PLUGIN_${APP_NAME_UC}_H
#define PLUGIN_${APP_NAME_UC}_H

#include <kparts/plugin.h>

class Plugin${APP_NAME} : public KParts::Plugin
{
  Q_OBJECT
public:
  Plugin${APP_NAME}( QObject* parent = 0, const char* name = 0, 
                     const QStringList &args = QStringList() );
  virtual ~Plugin${APP_NAME}();

public slots:
  void slotAction();
};

#endif // PLUGIN_${APP_NAME_UC}_H
