echo "Creating $LOCATION_ROOT/${APP_NAME_LC}/${APP_NAME_LC}view.cpp...";
cat << EOF > $LOCATION_ROOT/${APP_NAME_LC}/${APP_NAME_LC}view.cpp
#include "${APP_NAME_LC}view.h"

#include <qlayout.h>

#include <khtml.h>
#include <kcursor.h>

${APP_NAME}View::${APP_NAME}View(QWidget *parent)
    : QWidget(parent),
      DCOPObject("${APP_NAME}Iface")
{
    // setup our layout manager
    QHBoxLayout *top_layout = new QHBoxLayout(this);
    top_layout->setAutoAdd(true);

    // whatever widgets we have get automatically entered
    // into our layout manager
    m_html = new KHTMLWidget(this);
    connect(m_html, SIGNAL(onURL(const QString&)),
            this,   SLOT(slotOnURL(const QString&)));
    connect(m_html, SIGNAL(setTitle(const QString&)),
            this,   SLOT(slotSetTitle(const QString&)));
    m_html->setURLCursor(KCursor::handCursor());
    m_html->show();
}

${APP_NAME}View::~${APP_NAME}View()
{
}

QString ${APP_NAME}View::currentURL()
{
    return m_html->url();
}

void ${APP_NAME}View::openURL(QCString url)
{
    m_html->openURL(url);
}

void ${APP_NAME}View::slotOnURL(const QString& url)
{
    emit signalChangeStatusbar(url);
}

void ${APP_NAME}View::slotSetTitle(const QString& title)
{
    emit signalChangeCaption(title);
}
