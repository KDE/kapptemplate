echo "Creating $LOCATION_ROOT/$APP_NAME_LC/${APP_NAME_LC}iface.h...";
cat << EOF > $LOCATION_ROOT/$APP_NAME_LC/${APP_NAME_LC}iface.h
#ifndef ${APP_NAME_UC}IFACE_H
#define ${APP_NAME_UC}IFACE_H

#include <dcopobject.h>

class ${APP_NAME}Iface : virtual public DCOPObject
{
  K_DCOP
public:

k_dcop:
  virtual void openURL(QString url) = 0;
};

#endif // ${APP_NAME_UC}IFACE_H
