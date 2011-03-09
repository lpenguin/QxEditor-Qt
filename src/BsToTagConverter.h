#ifndef BSTOTAGCONVERTER_H
#define BSTOTAGCONVERTER_H
#include "BlockScript.h"
#include <QString>
#include <QStringList>
#include <QMap>
class BsToTagConverter
{
public:
    BsToTagConverter();
    QString TagStart() const ;
    QString TagEnd() const ;
    QString ConditionTagStart() const ;
    QString ConditionTagEnd() const ;

    QString ConditionTag( BsCondition * condition );
    QString ActionTag( BsAction * action );
    QString ObjectTag(BsObject * obj)  ;
    QString VariableTag(BsVariable * variable)  ;
    QString FunctionTag(BsFunction * function)  ;
    QString VariableDefinitionTag(BsVariableDefinition * varDef)  ;
    QString UserStringTag(BsUserString * userString)  ;
    QString ValueTag(BsValue * value)  ;
    QString ExpressionTag( BsOperator * expression)  ;
    QString NullTag( BsNull * null)  ;
    QString RangeTag( BsRange * range );

    QString ExpressionTypeToString(BsObject::BsOperation operation );
    QString ActionTypeToString(BsObject::BsOperation operation );
    QString ConditionTypeToString(BsCondition::BsConditionType condition );
private:
    QMap<BsObject::BsOperation, QString> m_expressionTypes;
    QMap<BsCondition::BsConditionType, QString> m_conditionTypes;
    QMap<BsObject::BsOperation, QString> m_actionTypes;
    void FillExpressionTypes();
    void FillActionTypes();
    void FillConditionTypes();

};

#endif // BSTOESMASCRIPTCONVERTER_H
