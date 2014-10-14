#ifndef AKONADI_SERIALIZER_%{APPNAMEUC}_H
#define AKONADI_SERIALIZER_%{APPNAMEUC}_H

#include <QtCore/QObject>

#include <akonadi/itemserializerplugin.h>

namespace Akonadi {

class SerializerPlugin%{APPNAME} : public QObject, public ItemSerializerPlugin
{
  Q_OBJECT
  Q_INTERFACES( Akonadi::ItemSerializerPlugin )

public:
  bool deserialize( Item& item, const QByteArray& label, QIODevice& data, int version );
  void serialize( const Item& item, const QByteArray& label, QIODevice& data, int &version );
  QSet<QByteArray> parts( const Item &item ) const;
};

}

#endif
