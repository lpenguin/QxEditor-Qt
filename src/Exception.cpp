#include "Exception.h"

Exception::Exception(QString message, QObject * parent )
    :m_message(message), QObject( parent )
{
}
