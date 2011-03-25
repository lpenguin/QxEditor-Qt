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

class QmEqToBsConverter
{
public:
    QmEqToBsConverter();
    void FillOperations();
    BsExpression * ParseEquation( const QString & equation) throw( ParseError );\
private:
    QString findOperator( const QString & expr, const QStringList & operators);

    OperationList m_operations;
};

#endif // QMEQTOBSCONVERTER_H
