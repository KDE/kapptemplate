echo "Creating $LOCATION_ROOT/${APP_NAME_LC}/${APP_NAME_LC}pref.h...";
cat << EOF > $LOCATION_ROOT/${APP_NAME_LC}/${APP_NAME_LC}pref.h
#ifndef ${APP_NAME_UC}PREF_H
#define ${APP_NAME_UC}PREF_H

#include <kdialogbase.h>
#include <qframe.h>

class ${APP_NAME}PrefPageOne;
class ${APP_NAME}PrefPageTwo;

class ${APP_NAME}Preferences : public KDialogBase
{
    Q_OBJECT
public:
    ${APP_NAME}Preferences();

private:
    ${APP_NAME}PrefPageOne *m_pageOne;
    ${APP_NAME}PrefPageTwo *m_pageTwo;
};

class ${APP_NAME}PrefPageOne : public QFrame
{
    Q_OBJECT
public:
    ${APP_NAME}PrefPageOne(QWidget *parent = 0);
};

class ${APP_NAME}PrefPageTwo : public QFrame
{
    Q_OBJECT
public:
    ${APP_NAME}PrefPageTwo(QWidget *parent = 0);
};

#endif // ${APP_NAME_UC}PREF_H
