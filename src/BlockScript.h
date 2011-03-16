#ifndef BSSCRIPT_H
#define BSSCRIPT_H

#include <QObject>

class BsVariable;
class BsAction;
class BlockScript;
class BsObject;
class BsStatement;
class BsVariableDefinition;
class BsCondition;
class BsExpression;
class BsRange;

typedef QList<BsObject * > BsObjectList;
typedef QList<BsCondition * > BsConditionList;
typedef QList<BsVariable * > BsVariableList;
typedef QList<BsStatement * > BsStatementList;
typedef QList<BsExpression * > BsExpressionList;
typedef QList<BsRange * > BsRangeList;
typedef BsObject * BsObjectP;

class BsObject : public QObject{
public:
    virtual int type() const = 0;
    enum  BsType{
        Variable, Action, Operator, Condition, Value, Range,/* List,*/ Function, If, UserString, Script, VariableDefinition, Null, UserType
    };
    enum  BsOperation{
           Addition, Substraction, Multiplication, Division, Show, Hide, None, Mov
    };
    static QString addQuotes(QString text){
        return QString("'%1'").arg(text);
    }
    bool isLocal( BsObjectP obj ){
        return obj->type() != BsObject::Variable;
    }

    void set( BsObjectP & obj, BsObjectP value );
    void setList( BsObjectList & list, BsObjectList value );
    void setList( BsExpressionList & list, BsExpressionList value );
    void setList( BsStatementList & list, BsStatementList value );
    void setList( BsConditionList & list, BsConditionList value );
    void setList( BsRangeList & list, BsRangeList value );
    void add( BsExpressionList & list, BsExpression * value);
    void add( BsObjectList & list, BsObject * value);
    void add( BsStatementList & list, BsStatement * value);
    void add( BsRangeList & list, BsRange * value);
};

class BsStatement : public BsObject {

};

class BsExpression : public BsObject {

};

class BsFunction : public BsExpression, public BsStatement{
private:
    QString m_name;
    BsExpressionList m_arguments;
public:
    BsFunction(QString name, BsExpressionList arguments):
        m_name(name){
            BsExpression::setList( m_arguments ,  arguments  );}
    QString name() const { return m_name; }
    BsExpressionList arguments() const { return m_arguments; }
    virtual int type() const { return BsObject::Function; }
};

class BsOperator : public BsExpression{
private:
    BsObject::BsOperation m_operation;
    BsExpressionList m_arguments;
public:
    BsOperator(BsObject::BsOperation operation = None, BsExpressionList arguments = BsExpressionList()):
        m_operation(operation)
    {
        setList( m_arguments, arguments );
    }

    BsObject::BsOperation operation() const { return m_operation; }
    BsExpressionList arguments() const { return m_arguments; }
    virtual int type() const { return BsObject::Operator; }
    void setOperation( BsObject::BsOperation value){ m_operation = value; }
    void addArgument( BsExpression * object ){ add( m_arguments, object );}
    void clearArguments() { m_arguments.clear(); }
};

//class BsList : public BsObject{
//private:
//    BsObjectList m_arguments;
//public:
//    BsExpression( BsObjectList arguments = BsObjectList())
//    {
//        setList( m_arguments, arguments );
//    }

//    BsObjectList arguments() const { return m_arguments; }
//    virtual int type() const { return BsObject::List; }
//    void addArgument( BsObject * object ){ add( m_arguments, object );}
//    void clearArguments() { m_arguments.clear(); }
//};

class BsCondition : public BsExpression{

public:
    enum BsConditionType{
        Equals, Greater, GreaterEq, Lower, LowerEq, And, Or, Not, In, Multiple, UserString
    };
private:
    BsConditionType m_condition;
    BsExpressionList m_arguments;
public:
    BsCondition(BsCondition::BsConditionType condition = Equals, BsExpressionList arguments = BsExpressionList()):
        m_condition(condition)
    {
        setList( m_arguments, arguments );
    }

    BsCondition::BsConditionType condition() const { return m_condition; }
    BsExpressionList arguments() const { return m_arguments; }
    void setCondition( BsCondition::BsConditionType value){ m_condition = value; }
    void addArgument( BsExpression * object ){ add( m_arguments, object );}
    void clearArguments() { m_arguments.clear(); }
    virtual int type() const { return BsObject::Condition; }
    static BsExpressionList ConditionsToExpressions(BsConditionList list){
        BsExpressionList elist;
        foreach( BsCondition * cond, list){
            elist<<(BsExpression*)cond;
        }
        return elist;
    }
};

class BsUserString : public BsStatement, public BsExpression{
private:
    QString m_string;
public:
    BsUserString(QString string):m_string(string){}
    QString string() const { return m_string; }
    virtual int type() const { return BsObject::UserString; }
};

class BsNull : public BsExpression{

public:
    virtual int type() const { return BsObject::Null; }
};

class BsValue : public BsExpression{
private:
    QString m_value;
public:
    BsValue(QString value):m_value(value){}
    QString value() const { return m_value; }
    virtual int type() const { return BsObject::Value; }
};

class BsVariable : public BsExpression{
private:
    QString m_name;
public:
    BsVariable(QString name):m_name(name){}
    QString name() const { return m_name; }
    virtual int type() const { return BsObject::Variable; }
};

class BsRange : public BsExpression {
private:
    BsExpression * m_min;
    BsExpression * m_max;
public:
    BsRange( BsExpression * min, BsExpression * max ){
        setMin(min);
        setMax(max);
    }
    virtual int type() const { return BsObject::Range; }
    BsExpression * min() { return m_min; }
    BsExpression * max() { return m_max; }
    void setMin( BsExpression * min ){
        set( (BsObjectP&)m_min, (BsObjectP)min);
    }
    void setMax( BsExpression * max ){
        set( (BsObjectP&)m_max, (BsObjectP)max);
    }
};

class BsVariableDefinition : public BsStatement {
private:
    BsExpression * m_value;
    BsVariable * m_var;
public:
    BsVariableDefinition( BsVariable * var, BsExpression * value );
    BsVariable * var() { return m_var; }
    void setVar( BsVariable * var ){
        set( (BsObjectP&)m_var, (BsObjectP)var);
    }
    BsExpression * value() { return m_value; }
    void setValue( BsExpression * value ){ set( (BsObjectP&)m_value, (BsObjectP)value); }
    virtual int type() const { return BsObject::VariableDefinition; }
};

class BsAction : public BsStatement{
public:
//    enum  BsActionType{
//            Addition, Substraction, Multiplication, Division, Show, Hide, None, UserString
//    };
private:
    BsVariable * m_var;
    BsExpression * m_value;
    BsObject::BsOperation m_actionType;
public:

    BsAction( BsVariable * var = 0, BsExpression * value = 0, BsObject::BsOperation actionType = None);
    virtual int type() const { return BsObject::Action; }
    BsVariable * var() { return m_var; }
    BsExpression * value(){ return m_value; }
    BsObject::BsOperation actionType() const { return m_actionType; }
    void setActionType( BsObject::BsOperation value ){ m_actionType = value; }
    void setValue( BsExpression * value ){ set( (BsObjectP&)m_value, (BsObjectP)value); }
    void setVar( BsVariable * var ){ set( (BsObjectP &)m_var , var); }
};

class BsIf : public BsStatement{
private:
    BsExpression * m_expression;
    BsStatementList m_statements;
public:
    BsIf(BsExpression * expression = 0, BsStatementList statements = BsStatementList()){
        setExpression( expression );
        setStatements( statements );
    }

    void setExpression( BsExpression * expression ){
        set( (BsObjectP &)m_expression, expression );
    }
    void setStatements( BsStatementList statements){
        setList(m_statements, statements);
    }
    BsStatementList staements() const { return m_statements; }
    BsExpression * expression() const { return m_expression; }
    virtual int type() const { return BsObject::If; }

};

class BlockScript : public BsObject
{
private:
    BsStatementList m_statements;
public:
    BlockScript( BsStatementList statements = BsStatementList() );
    BsStatementList statements(){ return m_statements; }
    void AddStatement( BsStatement * statement ){ add( m_statements , statement); }
    void AddStatements( BsStatementList statements ){
        foreach( BsStatement * statement, statements){
            add( m_statements , statement);
        }
    }
    void ClearStatements() { m_statements.clear(); };
    virtual int type() const { return BsObject::Script; }
};

#endif // BSSCRIPT_H
