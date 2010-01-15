#include "%{APPNAMELC}plugin.h"
#include "%{APPNAMELC}view.h"

#include <KTextEditor/Document>
#include <KTextEditor/View>

#include <KPluginFactory>
#include <KPluginLoader>
#include <KLocale>
#include <KAction>
#include <KActionCollection>

K_PLUGIN_FACTORY(%{APPNAME}PluginFactory, registerPlugin<%{APPNAME}Plugin>("ktexteditor_%{APPNAMELC}");)
K_EXPORT_PLUGIN(%{APPNAME}PluginFactory("ktexteditor_%{APPNAMELC}", "ktexteditor_plugins"))

%{APPNAME}Plugin::%{APPNAME}Plugin(QObject *parent, const QVariantList &args)
: KTextEditor::Plugin(parent)
{
	Q_UNUSED(args);
}

%{APPNAME}Plugin::~%{APPNAME}Plugin()
{
}

void %{APPNAME}Plugin::addView(KTextEditor::View *view)
{
	%{APPNAME}View *nview = new %{APPNAME}View(view);
	m_views.append(nview);
}

void %{APPNAME}Plugin::removeView(KTextEditor::View *view)
{
	for(int z = 0; z < m_views.size(); z++)
	{
		if(m_views.at(z)->parentClient() == view)
		{
			%{APPNAME}View *nview = m_views.at(z);
			m_views.removeAll(nview);
			delete nview;
		}
	}
}

void %{APPNAME}Plugin::readConfig()
{
}

void %{APPNAME}Plugin::writeConfig()
{
}

%{APPNAME}View::%{APPNAME}View(KTextEditor::View *view)
: QObject(view)
, KXMLGUIClient(view)
, m_view(view)
{
	setComponentData(%{APPNAME}PluginFactory::componentData());
	
	KAction *action = new KAction(i18n("KTextEditor - %{APPNAME}"), this);
	actionCollection()->addAction("tools_%{APPNAMELC}", action);
	//action->setShortcut(Qt::CTRL + Qt::Key_XYZ);
	connect(action, SIGNAL(triggered()), this, SLOT(insert%{APPNAME}()));
	
	setXMLFile("%{APPNAMELC}ui.rc");
}

%{APPNAME}View::~%{APPNAME}View()
{
}

void %{APPNAME}View::insert%{APPNAME}()
{
	m_view->document()->insertText(m_view->cursorPosition(), i18n("Hello, World!"));
}

#include "%{APPNAMELC}view.moc"
