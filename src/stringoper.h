#ifndef STRINGOPER_H
#define STRINGOPER_H
#include <QtCore>
#include "ParseError.h"

qint32 FindBracketEnd( const QString & str, qint32 startIndex = 0,
                      const QChar & openBracket = QChar('('),
                      const QChar & closeBracket = QChar(')')) throw (ParseError);
qint32 FindQuoteEnd( const QString & str, qint32 startIndex = 0 ) throw (ParseError);
qint32 FindInScript( const QString & str, qint32 startIndex = 0, const QString & delim = QString(",") ) throw (ParseError);
//qint32 FindInScript( const QString & str, qint32 startIndex = 0, const QRegExp & delim = QRegExp(",") ) throw (ParseError);

QString unpackSpecialChars( const QString & str );
QStringList splitSmart( QString str, QString delim  = QString(",") );
QString midStr( const QString & str, qint32 left, qint32 right = 0);

#endif // STRINGOPER_H
