#ifndef BINARYREADER_H
#define BINARYREADER_H

#include <QFile>
class BinaryReader
{
private:
    QFile * m_file;
    qint32 m_pos;
public:
    void skipRawData(qint32 len);
    BinaryReader( QFile * file);
    qint32 ReadInt32();
    qint8 ReadByte();
    QString ReadString();
    bool ReadBool();
    qreal ReadReal();
    QString ReadChars( int len );
};

#endif // BINARYREADER_H
