echo "Creating $LOCATION_ROOT/${APP_NAME_LC}view.cpp...";
cat << EOF > $LOCATION_ROOT/${APP_NAME_LC}view.cpp
/*
 * ${APP_NAME_LC}view.cpp
 *
 * Copyright (C) 2007 $AUTHOR <$EMAIL>
 */
#include "${APP_NAME_LC}view.h"
#include "settings.h"

#include <klocale.h>
#include <QLabel>

${APP_NAME}View::${APP_NAME}View(QWidget *)
{
    ui_${APP_NAME_LC}view_base.setupUi(this);
    settingsChanged();
    setAutoFillBackground(true);
}

${APP_NAME}View::~${APP_NAME}View()
{

}

void ${APP_NAME}View::switchColors()
{
    // switch the foreground/background colors of the label
    QColor color = Settings::col_background();
    Settings::setCol_background( Settings::col_foreground() );
    Settings::setCol_foreground( color );

    settingsChanged();
}

void ${APP_NAME}View::settingsChanged()
{
    QPalette pal;
    pal.setColor( QPalette::Window, Settings::col_background());
    pal.setColor( QPalette::WindowText, Settings::col_foreground());
    ui_${APP_NAME_LC}view_base.kcfg_sillyLabel->setPalette( pal );

    // i18n : internationalization
    ui_${APP_NAME_LC}view_base.kcfg_sillyLabel->setText( i18n("This project is %1 days old",Settings::val_time()) );
    emit signalChangeStatusbar( i18n("Settings changed") );
}

#include "${APP_NAME_LC}view.moc"
