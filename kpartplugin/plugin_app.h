echo "Creating $LOCATION_ROOT/$APP_NAME_LC/plugin_${APP_NAME_LC}.h...";
cat << EOF > $LOCATION_ROOT/$APP_NAME_LC/plugin_${APP_NAME_LC}.h
#ifndef _PLUGIN_${APP_NAME_UC}_H
#define _PLUGIN_${APP_NAME_UC}_H

#include <kparts/plugin.h>
#include <klibloader.h>

class Plugin${APP_NAME} : public KParts::Plugin
{
  Q_OBJECT
public:
  Plugin${APP_NAME}( QObject* parent = 0, const char* name = 0 );
  virtual ~Plugin${APP_NAME}();

public slots:
  void slotAction();
};

class ${APP_NAME}Factory : public KLibFactory
{
  Q_OBJECT
public:
  ${APP_NAME}Factory();
  virtual ~${APP_NAME}Factory();

  virtual QObject* createObject( QObject* parent = 0, const char* pname = 0, const char* name = "QObject", const QStringList &args = QStringList() );

  static KInstance* instance();

private:
  static KInstance* s_instance;
};

#endif // _PLUGIN_${APP_NAME_UC}_H
