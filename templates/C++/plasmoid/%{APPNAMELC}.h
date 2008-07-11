// Here we avoid loading the header multiple times
#ifndef %{APPNAMEUC}_HEADER
#define %{APPNAMEUC}_HEADER
// We need the Plasma Applet headers
#include <KIcon>

#include <Plasma/Applet>
#include <Plasma/Svg>

class QSizeF;

// Define our plasma Applet
class %{APPNAME} : public Plasma::Applet
{
    Q_OBJECT
    public:
        // Basic Create/Destroy
        %{APPNAME}(QObject *parent, const QVariantList &args);
        ~%{APPNAME}();

        // The paintInterface procedure paints the applet to screen
        void paintInterface(QPainter *painter,
                const QStyleOptionGraphicsItem *option,
                const QRect& contentsRect);
        void init();

    private:
        Plasma::Svg m_svg;
        KIcon m_icon;
};
 
// This is the command that links your applet to the .desktop file
K_EXPORT_PLASMA_APPLET(%{APPNAMELC}, %{APPNAME})
#endif
