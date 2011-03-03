#include "BinaryReader.h"

BinaryReader::BinaryReader(QFile * file):m_file(file)
{
    m_pos = m_file->pos();
}

qint32 BinaryReader::ReadInt32()
{
    qint32 tmp;
    m_file->read((char*)&tmp, 4);
    m_pos = m_file->pos();
    return tmp;
}

qint8 BinaryReader::ReadByte()
{
    qint8 tmp;
    int pos = m_file->pos();
    m_file->read((char*)&tmp, 1);
    m_pos = m_file->pos();
    return tmp;
}

QString BinaryReader::ReadString()
{
    qint32 length = ReadInt32();
    return ReadChars( length );
}

bool BinaryReader::ReadBool()
{
    qint32 tmp = ReadInt32();
    return tmp == 1;
}

qreal BinaryReader::ReadReal()
{
    double tmp;
    m_file->read((char*)&tmp, sizeof(double));
    return tmp;
}

QString BinaryReader::ReadChars(int len)
{
    char *s;
    m_file->read(s, len * 2);
    m_pos = m_file->pos();
//    ushort * arr = new ushort[len];
//    ushort u;
//    for( int i = 0; i< len * 2; i+=2){
//        u = s[i];
//        u>>8;
//        u|=s[i+1];
//    }
    return QString( s );
}

void BinaryReader::skipRawData(qint32 len)
{
    m_file->read(len);
    m_pos = m_file->pos();
}
