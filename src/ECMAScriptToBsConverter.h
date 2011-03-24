#ifndef ECMASCRIPTTOBSCONVERTER_H
#define ECMASCRIPTTOBSCONVERTER_H
#include "BlockScript.h"
#include "QuestLogic.h"
#include <QtScript>

class ParseError : std::exception {
public:
    enum ErrorType{
        Odinary, MissingStatementEnd, UnknownTag, InvalidStatement, MissingQuoteEnd, MissingBracketEnd,
        MissingExpressionTagStart, MissingExpressionTagEnd
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
    QlLocationStatementList ConvertLocationStatements( const QStringList & list ) throw( ParseError );
    QlPathStatementList ConvertPathStatementList( const QStringList & list ) throw( ParseError );
    QlParametrList  ConvertParametrList( const QStringList & list ) throw( ParseError );
    BsExpression *  ConvertExpressionStatement( const QString & str ) throw( ParseError );
private:
    QString tagStart;
    QString tagEnd;
    QString expTagStart;
    QString expTagEnd;

    BsStatementList ConvertStatements( const QStringList & list, qint32 startIndex, qint32 endIndex ) throw( ParseError );
    BsStatement * ConvertStatement( const QStringList & list, qint32 & startIndex ) throw( ParseError );

    BsAction * ConvertAction( QStringList tags );
    BsIf * ConvertIf(QStringList tags, BsStatementList statements );
    BsFunctionCall * ConvertFunctionCall(QStringList tags );
    BsVariableDefinition * ConvertVariableDefinition(QStringList tags );
    QlTrigger * ConvertTrigger(QStringList tags, BsStatementList statements);
    QlBoundTrigger * ConvertBoundTrigger(QStringList tags, BsStatementList statements);
    QlConstraint * ConvertConstraint(QStringList tags );
    QlLocationTexts * ConvertLocationTexts(QStringList tags );
    QlShowVariable * ConvertShowVariable(QStringList tags );
    QlPathPassability * ConvertPathPassability(QStringList tags );
    QlPathPriority * ConvertPathPriority(QStringList tags );
    QlParametr * ConvertParametr(QStringList tags, BsStatementList statements);
    QlPathShowOrder * ConvertPathShowOrder(QStringList tags );

    BsExpression * ConvertExpression( const QString & tag );
    BsOperator * ConvertOperator(const QString &tag);
    BsCondition * ConvertCondition( const QString &tag );
    BsRange * ConvertRange( const QString &tag );
    BsUserString * ConvertUserString( const QString &tag );
    BsFunction * ConvertFunction( const QString &tag );
    BsVariable * ConvertVariable( const QString &tag );
    BsValue * ConvertValue( const QString &tag );

    QString ConvertString(QString value );
    qint32 FindTagEnd( const QStringList & list, qint32 startIndex = 0) const throw( ParseError );
    qint32 FindBracketEnd( const QString & str, qint32 startIndex = 0 ) const throw (ParseError);
    qint32 FindQuoteEnd( const QString & str, qint32 startIndex = 0 ) const throw (ParseError);
    qint32 FindNextComma( const QString & str, qint32 startIndex = 0 ) const throw (ParseError);

    qint32 tagType( QString tag );
    QString tagName( QString tag );
    QStringList tagArguments( const QString & tag );
    BsObject::BsOperation ConvertActionOperation( const QString & operation );
    BsCondition::BsConditionType ConvertConditionType( const QString & condition );
    BsOperator::BsOperation ConvertOperationType( const QString & operation );
    QString unpackSpecialChars( const QString & str ) const;
    QStringList splitSmart( const QString & str ) const;
    QString midStr( const QString & str, qint32 left, qint32 right = 0) const;

    QScriptValue parseTag( QString tag );
    void FillOperatorTypes();
    void FillActionTypes();
    void FillConditionTypes();
    void FillCharMap();

    QMap<QString, BsObject::BsOperation> m_operatorTypes;
    QMap<QString, BsCondition::BsConditionType> m_conditionTypes;
    QMap<QString, BsObject::BsOperation> m_actionTypes;
    QMap<QString, QString> m_charMap;

};

#endif // ECMASCRIPTTOBSCONVERTER_H
