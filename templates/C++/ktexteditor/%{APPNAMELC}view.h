#ifndef %{APPNAMEUC}VIEW_H
#define %{APPNAMEUC}VIEW_H

#include <QObject>
#include <KXMLGUIClient>

class %{APPNAME}View : public QObject, public KXMLGUIClient
{
	Q_OBJECT
	public:
		explicit %{APPNAME}View(KTextEditor::View *view = 0);
		~%{APPNAME}View();
	private slots:
		void insert%{APPNAME}();
	private:
		KTextEditor::View *m_view;
};

#endif
