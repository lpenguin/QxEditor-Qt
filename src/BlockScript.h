#ifndef BSSCRIPT_H
#define BSSCRIPT_H

#include <QObject>

#define ISLOCAL( a ) ( /*a->type() != BsObject::Variable*/ 1 )
#define SETPARENT( a ) if( a && ISLOCAL(a)) a->setParent( this );
#define SETP(a, b) { \
    a = b; \
    SETPARENT(a) \
    }

#define SETPA(a) SETP( m_##a, a )

#define FOR( start, size ) for( int i = start; i < size; i++)

#define FORL( a ) FOR( 0, a.count())

#define SETL( a, b ) {\
    a.clear();\
    FORL(b){ \
    SETPARENT(b[i]);\
    a.append( b[i] );\
    } \
    }

#define SETLA( a ) SETL( m_##a, a )

#define ADDL( list, a ) {\
    list.append(a);\
    SETPARENT( a )\
    }

namespace BlockScript{

class BsVariable;
class BsAction;
class BsScript;
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
    //    BsObject( QObject * parent ):
    //        QObject( parent ){}
    virtual int type() const = 0;
    enum  BsType{
        Default, Variable, Action, Operator, Condition, Value, Set, Range,/* List,*/ Function,  FunctionCall, If, UserString, Script, VariableDefinition, Null, UserType
    };
    enum  BsOperation{
        Addition, Substraction, Multiplication, Division, Div, Mod, Show, Hide, None, Mov
    };
    static QString addQuotes(QString text){
        return QString("'%1'").arg(text);
    }
    bool isLocal( BsObjectP obj ){
        return 1;
        //        return obj->type() != BsObject::Variable;
    }

    //    void set( BsObjectP & obj, BsObjectP value );
    //    void setList( BsObjectList & list, BsObjectList value );
    //    void setList( BsExpressionList & list, BsExpressionList value );
    //    void setList( BsStatementList & list, BsStatementList value );
    //    void setList( BsConditionList & list, BsConditionList value );
    //    void setList( BsRangeList & list, BsRangeList value );
    //    void add( BsExpressionList & list, BsExpression * value);
    //    void add( BsObjectList & list, BsObject * value);
    //    void add( BsStatementList & list, BsStatement * value);
    //    void add( BsRangeList & list, BsRange * value);
};

class BsStatement : public BsObject {
    //public:
    //    BsStatement(){}
};

class BsExpression : public BsObject {
    //    BsExpression(){}
};

class BsFunction : public BsExpression{
private:
    QString m_name;
    BsExpressionList m_arguments;
public:
    //BsFunction(QString name, BsExpressionList arguments);
    BsFunction(QString name, BsExpressionList arguments){
        setName( name );
        setArguments( arguments );
    }
    QString name() const { return m_name; }
    BsExpressionList arguments() const { return m_arguments; }
    virtual int type() const { return BsObject::Function; }
    void setName( QString name ) {
        m_name = name;
    }
    void setArguments( BsExpressionList arguments ){
        SETLA( arguments )
    }
};

class BsFunctionCall : public BsStatement{
private:
    QString m_name;
    BsExpressionList m_arguments;
public:
    BsFunctionCall(QString name, BsExpressionList arguments){
        setName( name );
        setArguments( arguments );
    }

    QString name() const { return m_name; }
    BsExpressionList arguments() const { return m_arguments; }
    void setName( QString name ) {
        m_name = name;
    }
    void setArguments( BsExpressionList arguments ){
        SETLA( arguments )
    }
    virtual int type() const {
        return BsObject::FunctionCall;
    }
};

class BsOperator : public BsExpression{
private:
    BsObject::BsOperation m_operation;
    BsExpressionList m_arguments;
public:
    BsOperator(BsObject::BsOperation operation = None, BsExpressionList arguments = BsExpressionList()):
        m_operation(operation)
    {
        SETLA( arguments );
    }

    BsObject::BsOperation operation() const { return m_operation; }
    BsExpressionList arguments() const { return m_arguments; }
    virtual int type() const { return BsObject::Operator; }
    void setOperation( BsObject::BsOperation operation){ m_operation = operation; }
    void addArgument( BsExpression * object ){ ADDL( m_arguments, object );}
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

class BsSet : public BsExpression {
public:
    BsSet( BsExpressionList elems = BsExpressionList() ){
        setElems( elems );
    }

    BsExpressionList elems() const{
        return m_elems;
    }

    void setElems( BsExpressionList elems ){
        SETLA( elems )
    }
    virtual int type() const{
        return BsObject::Set;
    }
private:
   BsExpressionList m_elems;
};

class BsCondition : public BsExpression{

public:
    enum BsConditionType{
        None, Equals, NotEquals, Greater, GreaterEq, Lower, LowerEq, And, Or, Not, In, Multiple, UserString
    };
private:
    BsConditionType m_condition;
    BsExpressionList m_arguments;
public:
    BsCondition(BsCondition::BsConditionType condition = Equals, BsExpressionList arguments = BsExpressionList()):
        m_condition(condition)
    {
        SETLA( arguments );
    }

    BsCondition::BsConditionType condition() const { return m_condition; }
    BsExpressionList arguments() const { return m_arguments; }
    void setCondition( BsCondition::BsConditionType value){ m_condition = value; }
    void addArgument( BsExpression * object ){ ADDL( m_arguments, object );}
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
    BsValue(QString value = QString()):m_value(value){}
    QString value() const { return m_value; }
    virtual int type() const { return BsObject::Value; }
};

class BsVariable : public BsExpression{
private:
    QString m_name;
public:
    BsVariable(QString name = QString()):m_name(name){}
    QString name() const { return m_name; }
    virtual int type() const { return BsObject::Variable; }
};

class BsRange : public BsExpression {
private:
    BsExpression * m_min;
    BsExpression * m_max;
    bool m_calcRandom;//если true вычислять рандомное значение, иначе воспринимать как числовой диапазон
public:
    BsRange( BsExpression * min, BsExpression * max, bool calcRandom ){
        setMin(min);
        setMax(max);
        setCalcRandom( calcRandom );
    }
    virtual int type() const { return BsObject::Range; }
    BsExpression * min() { return m_min; }
    BsExpression * max() { return m_max; }
    void setMin( BsExpression * min ){
        SETPA( min )
                //        set( (BsObjectP&)m_min, (BsObjectP)min);
    }
    void setMax( BsExpression * max ){
        SETPA( max );
    }

    void setCalcRandom( bool calcRandom ){
        m_calcRandom = calcRandom;
    }

    bool calcRandom() const{
        return m_calcRandom;
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
        SETPA( var )
    }
    BsExpression * value() { return m_value; }
    void setValue( BsExpression * value ){ SETPA(value) }
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

    BsAction( BsVariable * var = new BsVariable(), BsExpression * value = new BsValue(), BsObject::BsOperation actionType = None);
    virtual int type() const { return BsObject::Action; }
    BsVariable * var() { return m_var; }
    BsExpression * value(){ return m_value; }
    BsObject::BsOperation actionType() const { return m_actionType; }
    void setActionType( BsObject::BsOperation value ){ m_actionType = value; }
    void setValue( BsExpression * value ){ SETPA( value ) }
    void setVar( BsVariable * var ){  SETPA( var ) }
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
        SETPA( expression )
    }
    void setStatements( BsStatementList statements){
        SETLA( statements )
    }
    BsStatementList staements() const { return m_statements; }
    BsExpression * expression() const { return m_expression; }
    virtual int type() const { return BsObject::If; }

};

class BsScript : public BsObject
{
private:
    BsStatementList m_statements;
public:
    BsScript( BsStatementList statements = BsStatementList() );
    BsStatementList statements(){ return m_statements; }
    void AddStatement( BsStatement * statement ){ ADDL( m_statements , statement); }
    void AddStatements( BsStatementList statements ){
        foreach( BsStatement * statement, statements){
            ADDL( m_statements , statement);
        }
    }
    void ClearStatements() { m_statements.clear(); };
    virtual int type() const { return BsObject::Script; }
};
}
#endif // BSSCRIPT_H
