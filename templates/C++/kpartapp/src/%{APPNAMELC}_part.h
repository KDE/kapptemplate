#ifndef %{APPNAMEUC}PART_H
#define %{APPNAMEUC}PART_H

#include <kparts/part.h>

class QWidget;
class QPainter;
class KUrl;
class QTextEdit;
class KAboutData;
class KAction;

/**
 * This is a "Part".  It that does all the real work in a KPart
 * application.
 *
 * @short Main Part
 * @author %{AUTHOR} <%{EMAIL}>
 * @version ${APP_VERSION}
 */
class %{APPNAME}Part : public KParts::ReadWritePart
{
    Q_OBJECT
public:
    /**
     * Default constructor
     */
    %{APPNAME}Part(QWidget *parentWidget,QObject *parent, const QStringList &);

    /**
     * Destructor
     */
    virtual ~%{APPNAME}Part();

    /**
     * This is a virtual function inherited from KParts::ReadWritePart.
     * A shell will use this to inform this Part if it should act
     * read-only
     */
    virtual void setReadWrite(bool rw);

    /**
     * Reimplemented to disable and enable Save action
     */
    virtual void setModified(bool modified);

    static KAboutData *createAboutData();

protected:
    /**
     * This must be implemented by each part
     */
    virtual bool openFile();

    /**
     * This must be implemented by each read-write part
     */
    virtual bool saveFile();
    KAction *save;

protected slots:
    void fileSaveAs();

private:
    QTextEdit *m_widget;
};

#endif // %{APPNAMEUC}PART_H
