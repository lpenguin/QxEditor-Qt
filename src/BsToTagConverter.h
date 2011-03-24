#ifndef BSTOTAGCONVERTER_H
#define BSTOTAGCONVERTER_H
#include "BlockScript.h"
#include "QuestLogic.h"
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
    QString packSpecialChars( QString ) const;

    QString ConditionTag( BsCondition * condition );
    QString ActionTag( BsAction * action );
    QString ExpressionTag(BsExpression * obj)  ;
    QString VariableTag(BsVariable * variable)  ;
    QString FunctionTag(BsFunction * function)  ;
    QString FunctionCallTag(BsFunctionCall * function)  ;
    QString VariableDefinitionTag(BsVariableDefinition * varDef)  ;
    QString UserStringTag(BsUserString * userString)  ;
    QString ValueTag(BsValue * value)  ;
    QString OperatorTag( BsOperator * expression)  ;
    QString NullTag( BsNull * null)  ;
    QString RangeTag( BsRange * range );
    QString IfTag( BsIf * if_);

    QString ConstraintTag( QlConstraint * con);
    QString TriggerTag( QlTrigger * trig);
    QString BoundTriggerTag( QlBoundTrigger * trig);
    QString ShowVariableTag( QlShowVariable * sv);
    QString ParametrTag(QlParametr * par);
    QString LocationTextsTag( QlLocationTexts * texts );
    QString PathPriorityTag( QlPathPriority * prior);
    QString PathPassabilityTag( QlPathPassability * pass);
    QString PathShowOrderTag( QlPathShowOrder * order);

    QString ExpressionTypeToString(BsObject::BsOperation operation );
    QString ActionTypeToString(BsObject::BsOperation operation );
    QString ConditionTypeToString(BsCondition::BsConditionType condition );
private:
    QMap<BsObject::BsOperation, QString> m_operatorTypes;
    QMap<BsCondition::BsConditionType, QString> m_conditionTypes;
    QMap<BsObject::BsOperation, QString> m_actionTypes;
    QMap<QString, QString> m_charMap;
    void FillOperatorTypes();
    void FillActionTypes();
    void FillConditionTypes();
    void FillCharMap();
};

#endif // BSTOESMASCRIPTCONVERTER_H
