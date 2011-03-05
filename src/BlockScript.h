#ifndef BSSCRIPT_H
#define BSSCRIPT_H

#include <QObject>

class BsVariable;
class BsAction;
class BlockScript;
class BsObject;
class BsInstruction;
class BsVariableDefinition;

typedef QList<BsObject * > BsObjectList;
typedef QList<BsVariable * > BsVariableList;
//typedef QList<BsAction * > BsActionList;
typedef QList<BsInstruction * > BsInstructionList;
typedef BsObject * BsObjectP;

class BsObject : QObject{
public:
    virtual int type() const = 0;
    enum  BsType{
        Variable, Action, Expression, Value, Function, UserString, VariableDefinition, Null
    };
    enum  BsOperation{
           Addition, Substraction, Multiplication, Division, Show, Hide, None, Mov
    };
    static QString addQuotes(QString text){
        return QString("'%1'").arg(text);
    }
    bool isLocal( BsObjectP obj ){
        switch( obj->type() ){
        case Value:
        case Expression:
        case Null:
        case UserString:
            return true;
        }
        return false;
    }

    void set( BsObjectP & obj, BsObjectP value ){
        obj = value;
        if( isLocal( obj ))
            obj->setParent( this );
    }
    void setList( BsObjectList & list, BsObjectList value ){
        foreach( BsObject * obj, value ){
            add( list, obj);
        }
    }

    void add( BsObjectList & list, BsObject * value){
        list.append( value );
        if( isLocal( value ))
            value->setParent( this );
    }
};

class BsInstruction : public BsObject {

};

class BsFunction : public BsInstruction{
private:
    QString m_name;
    BsObjectList m_arguments;
public:
    BsFunction(QString name, BsObjectList arguments):
        m_name(name){ setList( m_arguments, arguments );}
    QString name() const { return m_name; }
    BsObjectList arguments() const { return m_arguments; }
    virtual int type() const { return BsObject::Function; }
};

class BsExpression : public BsObject{
private:
    BsObject::BsOperation m_operation;
    BsObjectList m_arguments;
public:
    BsExpression(BsObject::BsOperation operation = None, BsObjectList arguments = BsObjectList()):
        m_operation(operation)
    {
        setList( m_arguments, arguments );
    }

    BsObject::BsOperation operation() const { return m_operation; }
    BsObjectList arguments() const { return m_arguments; }
    virtual int type() const { return BsObject::Expression; }
    void setOperation( BsObject::BsOperation value){ m_operation = value; }
    void addArgument( BsObject * object ){ add( m_arguments, object );}
    void clearArguments() { m_arguments.clear(); }
};

class BsUserString : public BsInstruction{
private:
    QString m_string;
public:
    BsUserString(QString string):m_string(string){}
    QString string() const { return m_string; }
    virtual int type() const { return BsObject::UserString; }
};

class BsNull : public BsObject{

public:
    virtual int type() const { return BsObject::Null; }
};

class BsValue : public BsObject{
private:
    QString m_value;
public:
    BsValue(QString value):m_value(value){}
    QString value() const { return m_value; }
    virtual int type() const { return BsObject::Value; }
};

class BsVariable : public BsObject{
private:
    QString m_name;
public:
    BsVariable(QString name):m_name(name){}
    QString name() const { return m_name; }
    virtual int type() const { return BsObject::Variable; }
};

class BsVariableDefinition : public BsInstruction {
private:
    BsObject * m_value;
    BsVariable * m_var;
public:
    BsVariableDefinition( BsVariable * var, BsValue * value );
    BsVariable * var() { return m_var; }
    void setVar( BsVariable * var ){
        set( (BsObjectP&)m_var, (BsObjectP)var);
    }
    BsObject * value() { return m_value; }
    void setValue( BsObject * value ){ set(m_value, value); }
};

class BsAction : public BsInstruction{
public:
//    enum  BsActionType{
//            Addition, Substraction, Multiplication, Division, Show, Hide, None, UserString
//    };
private:
    BsVariable * m_var;
    BsObject * m_value;
    BsObject::BsOperation m_actionType;
public:

    BsAction( BsVariable * var = 0, BsObject * value = 0, BsObject::BsOperation actionType = None);
    virtual int type() const { return BsObject::Action; }
    BsVariable * var() { return m_var; }
    BsObject * value(){ return m_value; }
    BsObject::BsOperation actionType() const { return m_actionType; }
    void setActionType( BsObject::BsOperation value ){ m_actionType = value; }
    void setValue( BsObject * value ){ set( m_value, value); }
    void setVar( BsVariable * var ){ set( (BsObjectP &)m_var , var); }
};


class BlockScript : public QObject
{
    Q_OBJECT
private:
    BsInstructionList m_instructions;
public:
    explicit BlockScript(QObject *parent = 0);
    BsInstructionList instructions(){ return m_instructions; }
    void AddInstruction( BsInstruction * instruction ){ m_instructions.append(instruction); }
    void AddInstructions( BsInstructionList instructions ){ m_instructions.append(instructions); }
    void ClearActions() { m_instructions.clear(); };
signals:

public slots:

};

#endif // BSSCRIPT_H
