#ifndef %{APPNAMEUC}PLUGIN_H
#define %{APPNAMEUC}PLUGIN_H

#include <QObject>

#include <QStringList>

class %{APPNAME}Plugin : public QObject
{
public:
    %{APPNAME}Plugin(QObject *parent = 0, const QStringList& args = QStringList());
};

#endif // %{APPNAME}Plugin.h
