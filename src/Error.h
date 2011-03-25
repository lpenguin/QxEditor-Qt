#ifndef EXCEPTION_H
#define EXCEPTION_H

#include <QtCore>
class Error : QObject
{
public:
    Q_PROPERTY( QString message READ message WRITE setMessage)
    Error(QString message = QString(), QObject * parent = 0 );
    Error( const Error & e ):
        m_message( e.m_message ){

    }

    QString message() const
    {
        return m_message;
    }
public slots:
    void setMessage(QString arg)
    {
        m_message = arg;
    }
private:
    QString m_message;
};
//class ReaderError  {
//public:

//    ReaderError( QString message = QString() ):
//        m_message(message){}

////    ~ParseError() throw() {}

//    QString message() const {
//        return m_message;
//    }

//    void setMessage( QString message ){
//        m_message = message;
//    }
//private:
//    QString m_message;
//};
#endif // EXCEPTION_H
