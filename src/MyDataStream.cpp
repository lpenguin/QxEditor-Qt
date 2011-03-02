#include "MyDataStream.h"

MyDataStream::MyDataStream(QFile * file):QDataStream(file)
{

}

qint32 MyDataStream::ReadInt32()
{
    qint32 tmp;
    *this>>tmp;
    return tmp;
}

qint8 MyDataStream::ReadByte()
{
    qint8 tmp;
    *this>>tmp;
    return tmp;
}

QString MyDataStream::ReadString()
{
    qint32 length = ReadInt32();
    return ReadChars( length );
}

bool MyDataStream::ReadBool()
{
    qint32 tmp = ReadInt32();
    return tmp == 1;
}

qreal MyDataStream::ReadReal()
{
    double tmp;
    *this>>tmp;
    return tmp;
}

QString MyDataStream::ReadChars(int len)
{
    char *s;
    readRawData(s, len * 2);
//    ushort * arr = new ushort[len];
//    ushort u;
//    for( int i = 0; i< len * 2; i+=2){
//        u = s[i];
//        u>>8;
//        u|=s[i+1];
//    }
    return QString( s );
}
