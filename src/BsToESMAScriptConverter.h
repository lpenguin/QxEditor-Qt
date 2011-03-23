#ifndef BSTOESMASCRIPTCONVERTER_H
#define BSTOESMASCRIPTCONVERTER_H

#include "BsToTagConverter.h"

class BsToESMAScriptConverter
{
public:
    BsToESMAScriptConverter();
    QString ConvertBlockSript( BlockScript * script);
    QString ConvertBsConditionStatement( BsExpression *object );
    QString ConvertQlParametr(QlParametr * parametr);
    QString ConvertQlParametrList(QlParametrList list);
    QString ConvertQlLocationTexts( QlLocationTexts * texts );
    QString ConvertQlPathStatementList( QlPathStatementList list );
private:
    QString ConvertBsExpression(BsExpression *obj);
    QString ConvertBsStatements(BsStatementList instructions);
    QString ConvertBsStatement(BsStatement *instruction);

    QString ConvertBsAction( BsAction * action );
    QString ConvertBsIf( BsIf * if_ );
    QString ConvertBsFunction( BsFunction * function );
    QString ConvertBsFunctionCall( BsFunctionCall * function );
    QString ConvertBsVariableDefinition( BsVariableDefinition * varDef );
    QString ConvertBsUserString( BsUserString * userString );
    QString ConvertBsVariable( BsVariable * variable );
    QString ConvertBsValue( BsValue * value );
    QString ConvertBsOperator( BsOperator * expression );
    QString ConvertBsRange( BsRange * range );
    QString ConvertBsCondition( BsCondition * condition );

    QString ConvertQlConstraint( QlConstraint * con);
    QString ConvertQlTrigger( QlTrigger * trig);
    QString ConvertQlBoundTrigger( QlBoundTrigger * trig);
    QString ConvertQlShowVariable( QlShowVariable * sv);

    QString ConvertQlPathPriority( QlPathPriority * priority );
    QString ConvertQlPathShowOrder( QlPathShowOrder * order );
    QString ConvertQlPathPassability( QlPathPassability * pass );

//    QString ConvertQlParametrStatement(QlParamStatement * statement );

    QString ExpressionTypeToString(BsObject::BsOperation operation );
    QString ActionTypeToString(BsObject::BsOperation operation );
    QString ConditionTypeToString(BsCondition::BsConditionType operation );
private:
    BsToTagConverter m_tagConverter;
    QMap<BsObject::BsOperation, QString> m_operatorTypes;
    QMap<BsObject::BsOperation, QString> m_actionTypes;
    QMap<BsCondition::BsConditionType, QString> m_conditionTypes;
//    QStringList ConvertBsObjectList( BsObjectList list );
    void FillOperatorTypes();
    void FillActionTypes();
    void FillConditionTypes();

};

#endif // BSTOESMASCRIPTCONVERTER_H
