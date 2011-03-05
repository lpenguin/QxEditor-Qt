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
    //QString ConvertBsInstructions( BsInstructionList instructions);
private:
    QMap<BsObject::BsOperation, QString> m_expressionTypes;
    QMap<BsObject::BsOperation, QString> m_actionTypes;
    void FillExpressionTypes();
    void FillActionTypes();
//    QString ConvertBsInstruction( BsInstruction * instruction );
//    QString ConvertBsAction( BsAction * action );
//    QString ConvertBsFunction( BsFunction * function, bool asLocal = false );
//    QString ConvertBsVariableDefinition( BsVariableDefinition * varDef );
//    QString ConvertBsUserString( BsUserString * userString );
//    QString ConvertBsVariable( BsVariable * variable );
//    QString ConvertBsValue( BsValue * value );
//    QString ConvertBsExpression( BsExpression * expression );
//    QString ConvertBsObject( BsObject * obj );

    QString TagStart() const ;
    QString TagEnd() const ;

    QString ActionTag( BsAction * action );
    QString ObjectTag(BsObject * obj)  ;
    QString VariableTag(BsVariable * variable)  ;
    QString FunctionTag(BsFunction * function)  ;
    QString VariableDefinitionTag(BsVariableDefinition * varDef)  ;
    QString UserStringTag(BsUserString * userString)  ;
    QString ValueTag(BsValue * value)  ;
    QString ExpressionTag( BsExpression * expression)  ;

    QString ExpressionTypeToString(BsObject::BsOperation operation );
    QString ActionTypeToString(BsObject::BsOperation operation );


};

#endif // BSTOESMASCRIPTCONVERTER_H
