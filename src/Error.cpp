#include "Error.h"

Error::Error(QString message, QObject * parent )
    :m_message(message), QObject( parent )
{
}
