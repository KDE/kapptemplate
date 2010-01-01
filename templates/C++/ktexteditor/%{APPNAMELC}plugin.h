#ifndef %{APPNAMEUC}PLUGIN_H
#define %{APPNAMEUC}PLUGIN_H

#include <KTextEditor/Plugin>

namespace KTextEditor
{
	class View;
}

class %{APPNAME}View;

class %{APPNAME}Plugin
  : public KTextEditor::Plugin
{
  public:
    // Constructor
    explicit %{APPNAME}Plugin(QObject *parent = 0, const QVariantList &args = QVariantList());
    // Destructor
    virtual ~%{APPNAME}Plugin();

    void addView (KTextEditor::View *view);
    void removeView (KTextEditor::View *view);
 
    void readConfig();
    void writeConfig();
 
//     void readConfig (KConfig *);
//     void writeConfig (KConfig *);
 
  private:
    QList<class %{APPNAME}View*> m_views;
};

#endif
