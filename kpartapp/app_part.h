echo "Creating $LOCATION_ROOT/${APP_NAME_LC}/${APP_NAME_LC}_part.h...";
cat << EOF > $LOCATION_ROOT/${APP_NAME_LC}/${APP_NAME_LC}_part.h
#ifndef ${APP_NAME_UC}PART_H
#define ${APP_NAME_UC}PART_H

#include <kparts/part.h>
#include <klibloader.h>

class QWidget;
class QPainter;
class KURL;
class QMultiLineEdit;

/**
 * This is a "Part".  It that does all the real work in a KPart
 * application.
 *
 * @short Main Part
 * @author ${AUTHOR} <${EMAIL}>
 * @version ${APP_VERSION}
 */
class ${APP_NAME}Part : public KParts::ReadWritePart
{
    Q_OBJECT
public:
    /**
     * Default constructor
     */
    ${APP_NAME}Part(QWidget *parent, const char *name);

    /**
     * Destructor
     */
    virtual ~${APP_NAME}Part();

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

protected:
    /**
     * This must be implemented by each part
     */
    virtual bool openFile();

    /**
     * This must be implemented by each read-write part
     */
    virtual bool saveFile();

protected slots:
    void fileOpen();
    void fileSaveAs();

private:
    QMultiLineEdit *m_widget;
};

class KInstance;
class KAboutData;

class ${APP_NAME}PartFactory : public KLibFactory
{
    Q_OBJECT
public:
    ${APP_NAME}PartFactory();
    virtual ~${APP_NAME}PartFactory();
    virtual QObject* create(QObject* parent = 0, const char* name = 0,
                            const char* classname = "QObject",
                            const QStringList &args = QStringList());
    static KInstance* instance();
 
private:
    static KInstance* s_instance;
    static KAboutData* s_about;
};

#endif // ${APP_NAME_UC}PART_H
