#ifndef QMEQTOBSCONVERTER_H
#define QMEQTOBSCONVERTER_H
#include "stringoper.h"
#include <QtCore>
#include "BlockScript.h"
#include "ParseError.h"

using namespace BlockScript;

enum QmOperation{
    Or, And, Comp, In, To, Math
};

typedef QPair<QmOperation, QStringList> OperatorPair;
typedef QList< OperatorPair > OperationList;

class
        QmEqToBsConverter
{
public:
    QmEqToBsConverter();
    BsExpression * parseExpression( const QString & equation) throw( ParseError );
private:
    QString findOperator( const QString & expr, const QStringList & operators);
    BsExpressionList parseExpressions( const QStringList & exprs ) throw( ParseError );
    BsExpression * parseArg( const QString & arg ) throw( ParseError );

    BsVariable * parseVariable( const QString & arg ) throw( ParseError );
    BsRange * parseRange( const QString & arg ) throw( ParseError );
    BsSet * parseSet( const QString & arg ) throw( ParseError );
    BsValue * parseValue( const QString & arg ) throw( ParseError );


    void FillOperations();
    void FillConditionTypes();
    void FillOperationTypes();

    bool isVariable( const QString & arg );
    bool isRange( const QString & arg );
    bool isSet( const QString & arg );
    bool isValue( const QString & arg );

    OperationList m_operations;
    QMap<QString, BsCondition::BsConditionType > m_conditionTypes;
    QMap<QString, BsObject::BsOperation > m_operationTypes;
};

#endif // QMEQTOBSCONVERTER_H
