echo "Creating $LOCATION_ROOT/${APP_NAME_LC}/${APP_NAME_LC}view.cpp...";
cat << EOF > $LOCATION_ROOT/${APP_NAME_LC}/${APP_NAME_LC}view.cpp
#include "${APP_NAME_LC}view.h"

#include <qpainter.h>
#include <qlayout.h>

#include <kurl.h>

#include <ktrader.h>
#include <klibloader.h>
#include <kmessagebox.h>
#include <krun.h>

${APP_NAME}View::${APP_NAME}View(QWidget *parent)
    : QWidget(parent),
      DCOPObject("${APP_NAME}Iface")
{
    // setup our layout manager to automatically add our widgets
    QHBoxLayout *top_layout = new QHBoxLayout(this);
    top_layout->setAutoAdd(true);

    // we want to look for all components that satisfy our needs.  the
    // trader will actually search through *all* registered KDE
    // applications and components -- not just KParts.  So we have to
    // specify two things: a service type and a constraint
    //
    // the service type is like a mime type.  we say that we want all
    // applications and components that can handle HTML -- 'text/html'
    // 
    // however, by itself, this will return such things as Netscape..
    // not what we wanted.  so we constrain it by saying that the
    // string 'KParts/ReadOnlyPart' must be found in the ServiceTypes
    // field.  with this, only components of the type we want will be
    // returned.
    KTrader::OfferList offers = KTrader::self()->query("text/html", "'KParts/ReadOnlyPart' in ServiceTypes");

    KLibFactory *factory = 0;
    // in theory, we only care about the first one.. but let's try all
    // offers just in case the first can't be loaded for some reason
    KTrader::OfferList::Iterator it(offers.begin());
    for( ; it != offers.end(); ++it)
    {
        KService::Ptr ptr = (*it);

        // we now know that our offer can handle HTML and is a part.
        // since it is a part, it must also have a library... let's try to
        // load that now
        factory = KLibLoader::self()->factory( ptr->library() );
        if (factory)
        {
            m_html = static_cast<KParts::ReadOnlyPart *>(factory->create(this, ptr->name(), "KParts::ReadOnlyPart"));
            break;
        }
    }

    // if our factory is invalid, then we never found our component
    // and we might as well just exit now
    if (!factory)
    {
        KMessageBox::error(this, "Could not find a suitable HTML component");
        return;
    }

    connect(m_html, SIGNAL(setWindowCaption(const QString&)),
            this,   SLOT(slotSetTitle(const QString&)));
    connect(m_html, SIGNAL(setStatusBarText(const QString&)),
            this,   SLOT(slotOnURL(const QString&)));

}

${APP_NAME}View::~${APP_NAME}View()
{
}

void ${APP_NAME}View::print(QPainter *p, int height, int width)
{
    // do the actual printing, here
    // p->drawText(etc..)
}

QString ${APP_NAME}View::currentURL()
{
    return m_html->url().url();
}

void ${APP_NAME}View::openURL(QString url)
{
    openURL(KURL(url));
}

void ${APP_NAME}View::openURL(const KURL& url)
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
#include "${APP_NAME_LC}view.moc"
