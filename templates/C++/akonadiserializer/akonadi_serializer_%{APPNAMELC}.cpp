#include "akonadi_serializer_%{APPNAMELC}.h"

#include <akonadi/item.h>

#include <QtCore/qplugin.h>

using namespace Akonadi;

bool SerializerPlugin%{APPNAME}::deserialize( Item& item, const QByteArray& label, QIODevice& data, int version )
{
  Q_UNUSED( item );
  Q_UNUSED( label );
  Q_UNUSED( data );
  Q_UNUSED( version );

  // TODO Implement this

  return false;
}

void SerializerPlugin%{APPNAME}::serialize( const Item& item, const QByteArray& label, QIODevice& data, int &version )
{
  Q_UNUSED( item );
  Q_UNUSED( label );
  Q_UNUSED( data );
  Q_UNUSED( version );

  // TODO Implement this
}

Q_EXPORT_PLUGIN2( akonadi_serializer_%{APPNAMELC}, Akonadi::SerializerPlugin%{APPNAME} )

#include "akonadi_serializer_%{APPNAMELC}.moc"
