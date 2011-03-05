#ifndef BSTOESMASCRIPTCONVERTER_H
#define BSTOESMASCRIPTCONVERTER_H

#include "BsToTagConverter.h"

class BsToESMAScriptConverter
{
public:
    BsToESMAScriptConverter();
    QString ConvertBsInstructions( BsInstructionList instructions);


    QString ConvertBsInstruction( BsInstruction * instruction );
    QString ConvertBsConditionInstruction( BsObject *object );
private:
    QString ConvertBsAction( BsAction * action );
    QString ConvertBsFunction( BsFunction * function );
    QString ConvertBsVariableDefinition( BsVariableDefinition * varDef );
    QString ConvertBsUserString( BsUserString * userString );
    QString ConvertBsVariable( BsVariable * variable );
    QString ConvertBsValue( BsValue * value );
    QString ConvertBsExpression( BsExpression * expression );
    QString ConvertBsObject( BsObject * obj );
    QString ConvertBsRange( BsRange * range );
    QString ConvertBsCondition( BsCondition * condition );

    QString ExpressionTypeToString(BsObject::BsOperation operation );
    QString ActionTypeToString(BsObject::BsOperation operation );
    QString ConditionTypeToString(BsCondition::BsConditionType operation );
private:
    BsToTagConverter m_tagConverter;
    QMap<BsObject::BsOperation, QString> m_expressionTypes;
    QMap<BsObject::BsOperation, QString> m_actionTypes;
    QMap<BsCondition::BsConditionType, QString> m_conditionTypes;
//    QStringList ConvertBsObjectList( BsObjectList list );
    void FillExpressionTypes();
    void FillActionTypes();
    void FillConditionTypes();

};

#endif // BSTOESMASCRIPTCONVERTER_H
