#ifndef %{APPNAMEUC}PLUGIN_H
#define %{APPNAMEUC}PLUGIN_H

#include <kparts/plugin.h>
#include <klibloader.h>
#include "ui_config.h"
#include <KParts/ReadOnlyPart>

class %{APPNAMELC}Plugin
            : public KParts::Plugin
{
    Q_OBJECT

public:
    // Constructor
    explicit %{APPNAMELC}Plugin(QObject *parent = 0, const QVariantList &args = QVariantList());
    // Destructor
    virtual ~%{APPNAMELC}Plugin();

    Ui_ConfigDialog		ui_configdialog;
    KParts::ReadOnlyPart	*m_Part;

protected slots:
    void showConfig();
};

#endif
