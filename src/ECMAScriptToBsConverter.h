#ifndef ECMASCRIPTTOBSCONVERTER_H
#define ECMASCRIPTTOBSCONVERTER_H
#include "BlockScript.h"
#include "QuestLogic.h"

class ParseError : std::exception {
public:
    enum ErrorType{
        Odinary, MissingStatementEnd, UnknownTag
    };

    ParseError( QString message = QString(), ErrorType errorType = Odinary ):
        m_message(message), m_errorType(errorType), exception(){}

    ~ParseError() throw() {}

    QString message() const {
        return m_message;
    }

    void setMessage( QString message ){
        m_message = message;
    }

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

class ECMAScriptToBsConverter
{
public:
    ECMAScriptToBsConverter();
    BlockScript * ConvertScript( const QStringList & list ) throw( ParseError );

private:
    QString tagStart;
    QString tagEnd;

    BsStatementList ConvertStatements( const QStringList & list, qint32 startIndex, qint32 endIndex ) throw( ParseError );

    BsAction * ConvertAction(const QStringList &list, qint32 &startIndex, const QString &line) throw( ParseError );
    BsIf * ConvertIf(const QStringList &list, qint32 &startIndex, const QString &line);
    BsStatement * ConvertStatement( const QStringList & list, qint32 & startIndex ) throw( ParseError );

    BsExpression * ConvertExpression( const QString & tag );
    BsOperator * ConvertOperator(const QString &tag);
    BsCondition * ConvertCondition( const QString &tag );
    BsRange * ConvertRange( const QString &tag );
    BsUserString * ConvertUserString( const QString &tag );
    BsFunction * ConvertFunction( const QString &tag );

    qint32 FindTagEnd( const QStringList & list, qint32 startIndex = 0) throw( ParseError );
    qint32 tagType( QString tag );
    QString tagName( QString tag );
    QStringList tagContents( const QString & tag );
    BsObject::BsOperation ConvertActionOperation( const QString & operation );
    BsCondition::BsConditionType ConvertConditionType( const QString & condition );
    BsOperator::BsOperation ConvertOperationType( const QString & operation );

    void FillOperatorTypes();
    void FillActionTypes();
    void FillConditionTypes();

    QMap<QString, BsObject::BsOperation> m_operatorTypes;
    QMap<QString, BsCondition::BsConditionType> m_conditionTypes;
    QMap<QString, BsObject::BsOperation> m_actionTypes;


};

#endif // ECMASCRIPTTOBSCONVERTER_H
