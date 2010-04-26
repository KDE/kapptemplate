#include "%{APPNAMELC}plugin.h"

#include <KPluginFactory>
#include <KPluginLoader>
#include <KLocale>
#include <KAction>
#include <KActionCollection>
#include <KAboutData>
#include <KDebug>
#include <KStandardDirs>
#include <KStandardAction>
#include <KMessageBox>
#include <KActionMenu>
#include <KConfigDialog>
#include <QGraphicsWidget>

#include "settings.h"

static const KAboutData aboutdata("%{APPNAMELC}plugin", 0, ki18n("%{APPNAME} Settings") , "0.1" );

K_PLUGIN_FACTORY(%{APPNAMELC}PluginFactory, registerPlugin<%{APPNAMELC}Plugin>(); )
K_EXPORT_PLUGIN(%{APPNAMELC}PluginFactory(aboutdata))


%{APPNAMELC}Plugin::%{APPNAMELC}Plugin(QObject *parent, const QVariantList &args)
        : KParts::Plugin(parent)
{
    Q_UNUSED(args);

    setComponentData(%{APPNAMELC}PluginFactory::componentData());

    m_Part = dynamic_cast<KParts::ReadOnlyPart *>(parent);
    if (! m_Part)
    {
        kDebug() << "Unable to get KHTMLPart" << endl;
        return;
    }

    kDebug() << "%{APPNAMELC} created" << endl;


    // Config Action
    QAction *actConfig = actionCollection()->addAction("configure_%{APPNAMELC}");
    actConfig->setText(i18n("&Configure %{APPNAME}"));
    
    // Setup our menu
    KActionMenu*menu = new KActionMenu("%{APPNAME}", actionCollection());
    actionCollection()->addAction("tools_%{APPNAMELC}", menu);
    connect(actConfig, SIGNAL(triggered(bool)), this, SLOT(showConfig()));
    menu->addAction(actConfig);
}

%{APPNAMELC}Plugin::~%{APPNAMELC}Plugin()
{
}


void %{APPNAMELC}Plugin::showConfig()
{
    kDebug() << "Configure %{APPNAMELC}" << endl;
    // The preference dialog is derived from config.ui
    //
    // compare the names of the widgets in the .ui file
    // to the names of the variables in the .kcfg file
    //avoid to have 2 dialogs shown
    if ( KConfigDialog::showDialog ( "settings" ) )
    {
        return;
    }
    KConfigDialog *dialog = new KConfigDialog ( NULL, "settings", Settings::self() );
    QWidget *generalSettingsDlg = new QWidget;
    ui_configdialog.setupUi ( generalSettingsDlg );
    dialog->addPage ( generalSettingsDlg, i18n ( "General" ), "package_setting" );
    //connect ( dialog, SIGNAL ( settingsChanged ( QString ) ), m_view, SLOT ( settingsChanged() ) );
    dialog->setAttribute ( Qt::WA_DeleteOnClose );
    dialog->show();

}

