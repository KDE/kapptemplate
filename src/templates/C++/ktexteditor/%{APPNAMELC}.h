#ifndef %{APPNAMEUC}_H
#define %{APPNAMEUC}_H

#include <KTextEditor/Plugin>
#include <KTextEditor/Range>
#include <KTextEditor/TextHintInterface>

#include <QVariantList>
#include <QList>

#include <KXMLGUIClient>

class %{APPNAME}Plugin;

class %{APPNAME}Plugin : public KTextEditor::Plugin
{
    Q_OBJECT

public:
    explicit %{APPNAME}Plugin(QObject *parent = 0, const QList<QVariant> & = QList<QVariant>());
    virtual ~%{APPNAME}Plugin();
    QObject *createView(KTextEditor::MainWindow *mainWindow);
};

class %{APPNAME}View: public QObject
{
    Q_OBJECT

public:
    %{APPNAME}View(%{APPNAME}Plugin *plugin, KTextEditor::MainWindow *view);
    virtual ~%{APPNAME}View();
};

#endif // %{APPNAMEUC}
