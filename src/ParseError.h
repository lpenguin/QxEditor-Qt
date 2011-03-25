#ifndef PARSEERROR_H
#define PARSEERROR_H
#include "Error.h"
#include <QString>

class ParseError : public Error {
public:
    enum ErrorType{
        Odinary, MissingStatementEnd, UnknownTag, InvalidStatement, MissingQuoteEnd, MissingBracketEnd,
        MissingExpressionTagStart, MissingExpressionTagEnd
    };

    ParseError( QString message = QString(), ErrorType errorType = Odinary ):
        m_errorType(errorType), Error(message){}


    ErrorType errorType() const {
        return m_errorType;
    }

    void setErrorType( ErrorType errorType ){
        m_errorType = errorType;
    }
private:
    QString m_message;
    ErrorType m_errorType;
};

#endif // PARSEERROR_H
