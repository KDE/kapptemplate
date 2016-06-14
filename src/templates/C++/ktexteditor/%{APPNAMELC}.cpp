#include "%{APPNAMELC}.h"

#include <KTextEditor/Document>
#include <KTextEditor/Range>
#include <KTextEditor/View>
#include <KTextEditor/CodeCompletionInterface>
#include <KTextEditor/CodeCompletionInterface>
#include <KTextEditor/TextHintInterface>
#include <KTextEditor/MainWindow>

#include <KPluginFactory>
#include <KActionCollection>
#include <KLocalizedString>

#include <QAction>
#include <QFile>
#include <QDir>

K_PLUGIN_FACTORY_WITH_JSON(%{APPNAME}PluginFactory, "%{APPNAMELC}.json", registerPlugin<%{APPNAME}Plugin>();)

%{APPNAME}Plugin::%{APPNAME}Plugin(QObject *parent, const QList<QVariant> &) : KTextEditor::Plugin(parent)
{
}

%{APPNAME}Plugin::~%{APPNAME}Plugin()
{
}

QObject* %{APPNAME}Plugin::createView(KTextEditor::MainWindow *mainwindow)
{
    return new %{APPNAME}View(this, mainwindow);
}

%{APPNAME}View::%{APPNAME}View(%{APPNAME}Plugin *plugin, KTextEditor::MainWindow *mainwindow) : QObject(mainwindow)
{
    Q_UNUSED(plugin);
}

%{APPNAME}View::~%{APPNAME}View()
{
}

#include "%{APPNAMELC}.moc"
