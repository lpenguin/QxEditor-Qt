#ifndef MYDATASTREAM_H
#define MYDATASTREAM_H

#include <QDataStream>
#include <QFile>
class MyDataStream : public QDataStream
{
public:
    MyDataStream( QFile * file);
    qint32 ReadInt32();
    qint8 ReadByte();
    QString ReadString();
    bool ReadBool();
    qreal ReadReal();
    QString ReadChars( int len );
};

#endif // MYDATASTREAM_H
