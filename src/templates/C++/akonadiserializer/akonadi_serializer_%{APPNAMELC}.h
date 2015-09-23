#ifndef AKONADI_SERIALIZER_%{APPNAMEUC}_H
#define AKONADI_SERIALIZER_%{APPNAMEUC}_H

#include <QtCore/QObject>

#include <AkonadiCore/ItemSerializerPlugin>

namespace Akonadi
{

class SerializerPlugin%{APPNAME} : public QObject
                                 , public ItemSerializerPlugin
{
    Q_OBJECT
    Q_INTERFACES(Akonadi::ItemSerializerPlugin)
    Q_PLUGIN_METADATA(IID "org.kde.akonadi.SerializerPlugin%{APPNAME}")

public:
    bool deserialize(Item &item, const QByteArray &label, QIODevice &data, int version) Q_DECL_OVERRIDE;
    void serialize(const Item &item, const QByteArray &label, QIODevice &data, int &version) Q_DECL_OVERRIDE;

    QSet<QByteArray> parts(const Item &item) const;
};

}

#endif
