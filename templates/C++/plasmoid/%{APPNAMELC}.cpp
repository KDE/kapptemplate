#include "%{APPNAMELC}.h"
#include <QPainter>
#include <QFontMetrics>
#include <QSizeF>
#include <KLocale>

#include <plasma/svg.h>
#include <plasma/theme.h>

%{APPNAME}::%{APPNAME}(QObject *parent, const QVariantList &args)
    : Plasma::Applet(parent, args),
    m_svg(this),
    m_icon("document")
{
    // this will get us the standard applet background, for free!
    setBackgroundHints(DefaultBackground);
    m_svg.setImagePath("widgets/background");
    setHasConfigurationInterface(true);  
    resize(200, 200);
}


%{APPNAME}::~%{APPNAME}()
{
    if (hasFailedToLaunch()) {
        // Do some cleanup here
    } else {
        // Save settings
    }
}

void %{APPNAME}::init()
{
    // A small demonstration of the setFailedToLaunch function
    if (m_icon.isNull()) {
        setFailedToLaunch(true, i18n("No world to say hello"));
    }
}


void %{APPNAME}::paintInterface(QPainter *p,
        const QStyleOptionGraphicsItem *option, const QRect &contentsRect)
{
    p->setRenderHint(QPainter::SmoothPixmapTransform);
    p->setRenderHint(QPainter::Antialiasing);

    // Now we draw the applet, starting with our svg
    m_svg.resize((int)contentsRect.width(), (int)contentsRect.height());
    m_svg.paint(p, (int)contentsRect.left(), (int)contentsRect.top());

    // We place the icon and text
    p->drawPixmap(7, 0, m_icon.pixmap((int)contentsRect.width(),(int)contentsRect.width()-14));
    p->save();
    p->setPen(Qt::white);
    p->drawText(contentsRect,
                Qt::AlignBottom | Qt::AlignHCenter,
                i18n("Hello Plasmoid!"));
    p->restore();
}

#include "%{APPNAMELC}.moc"
