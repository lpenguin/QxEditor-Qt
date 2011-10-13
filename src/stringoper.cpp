#include "stringoper.h"

qint32 FindQuoteEnd(const QString &str, qint32 startIndex) throw( ParseError )
{
    for(qint32 i = startIndex + 1; i < str.count(); i++){
        if( str[i] == '\'' )
            return i;
    }
    throw( ParseError(QString("Missing quote end in: %1 ( ==> %2 )").arg(str).arg(str.right( str.count() - startIndex )), ParseError::MissingQuoteEnd));
}

qint32 FindBracketEnd(const QString &str, qint32 startIndex,
                                               const QChar & openBracket,
                                               const QChar & closeBracket ) throw( ParseError )
{
    qint32 bracketCounter = 1, i;
    for(i = startIndex + 1; i < str.count() ; i++){
        QChar ch = str[i];
        if( str[i] == openBracket )
            bracketCounter++;
        else if( str[i] == closeBracket)
            bracketCounter--;
        if(!bracketCounter)
            return i;
    }
//    ParseError(QString("Missing quote end in: %1 ( ==> %2 )").arg(str).arg(str.truncate( startIndex ))
    if( bracketCounter ) throw( ParseError(QString("Missing bracket end in %1 ( ==> %2 )").arg(str).arg(str.right( str.count() - startIndex )), ParseError::MissingBracketEnd));
}

qint32 FindInScript(const QString &str, qint32 startIndex, const QString & delim) throw( ParseError )
{
    QString search = str;
    search.remove(0, startIndex );
    qint32 pos = startIndex, trunc;

    while( search.count() ){

        if( QRegExp("^"+delim).indexIn(search) == 0 ){
                return pos;
        }
        else if( search.startsWith( QChar( '(' ) ) ){
            trunc = FindBracketEnd( search );
        } else if(  search.startsWith('\'') ){
            trunc = FindQuoteEnd( search ) + 1;
        } else if( search.startsWith('[') )
            trunc = FindBracketEnd( search, 0, QChar('['), QChar(']') );
        else
            trunc = 1;
        pos += trunc;
        search.remove(0, trunc );
    }
    return -1;
}

/*qint32 FindInScript(const QString &str, qint32 startIndex, const QRegExp & delim) throw( ParseError )
{
    QString search = str;
    search.remove(0, startIndex );
    qint32 pos = startIndex, trunc;

    while( search.count() ){
        if( search.startsWith(delim) )
                return pos;
        else if( search.startsWith( QChar( '(' ) ) ){
            trunc = FindBracketEnd( search );
        } else if(  search.startsWith('\'') ){
            trunc = FindQuoteEnd( search ) + 1;
        } else if( search.startsWith('[') )
            trunc = FindBracketEnd( search, 0, QChar('['), QChar(']') );
        else
            trunc = 1;
        pos += trunc;
        search.remove(0, trunc );
    }
    return -1;
}*/


QStringList splitSmart(QString str, QString delim ) {
    QStringList result;
    int pos = 0;
    delim = delim.replace("+", "\\+")
            .replace(".", "\\.")
            .replace("*","\\*");

    delim = QRegExp("^\\w+$").indexIn(delim) == 0 ? "\\W+"+delim+"\\W+" : delim;

    while( (pos = FindInScript( str, 0, delim )) != -1 ){
        result << str.left( pos).trimmed();
        str = str.mid(pos).replace( QRegExp("^"+delim), "" );
    }
    result << str.trimmed();
    return result;
}

QString midStr(const QString &str, qint32 left, qint32 right) {
    return str.mid( left, str.count() - right - 1);
}
