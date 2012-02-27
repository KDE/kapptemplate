#ifndef %{APPNAMEUC}PLUGIN_H
#define %{APPNAMEUC}PLUGIN_H

#include <QObject>

class QVariantList;

class %{APPNAME}Plugin : public QObject
{
public:
    %{APPNAME}Plugin(QObject *parent, const QVariantList& args);
};

#endif // %{APPNAME}Plugin.h
