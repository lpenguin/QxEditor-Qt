#ifndef BSSCRIPT_H
#define BSSCRIPT_H

#include <QObject>

class BsVariable;
class BsAction;
class BlockScript;
class BsObject;
typedef QList<BsObject * > BsObjectList;
typedef QList<BsVariable * > BsVariableList;
typedef QList<BsAction * > BsActionList;

class BsObject{
public:
    virtual int type() const = 0;
    enum  BsType{
        Variable, Action, Expression, Value, Function, UserString, Null
    };
    enum  BsOperation{
            Addition, Substraction, Multiplication, Division, Mov
    };
    static QString addQuotes(QString text){
        return QString("'%1'").arg(text);
    }
};

class BsFunction : public BsObject{
private:
    QString m_name;
    BsObjectList m_arguments;
public:
    BsFunction(QString name, BsObjectList arguments):
        m_name(name),m_arguments(arguments){}
    QString name() const { return m_name; }
    BsObjectList arguments() const { return m_arguments; }
    virtual int type() const { return BsObject::Function; }
};

class BsExpression : public BsObject{
private:
    BsObject::BsOperation m_opertaion;
    BsObjectList m_arguments;
public:
    BsExpression(BsObject::BsOperation opertaion = OnlyValue, BsObjectList arguments = BsObjectList):
        m_opertaion(opertaion),m_arguments(arguments){}
    BsObject::BsOperation opertaion() const { return opertaion; }
    BsObjectList arguments() const { return m_arguments; }
    virtual int type() const { return BsObject::Expression; }
    void setOperation( BsObject::BsOperation value){ m_opertaion = value; }
    void addArgument( BsObject * object ){ m_arguments.append( object );}
    void clearArguments() { m_arguments.clear(); }
};

class BsUserString : public BsObject{
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

class BsAction : public BsObject{
private:
    BsVariable * m_var;
    BsObject * m_value;
    BsObject::BsActionType m_actionType;
public:
    enum  BsActionType{
            Addition, Substraction, Multiplication, Division, Show, Hide
    };
    BsAction( BsVariable * var, BsObject * value, BsObject::BsActionType actionType):
        m_var(var), m_value(value), m_actionType( actionType ){};
    virtual int type() const { return BsObject::Action; }
    BsVariable * var() { return m_var; }
    BsObject * value(){ return m_value; }
    BsAction::BsActionType actionType() const { return m_actionType; }
    void setActionType( BsAction::BsActionType value ){ m_actionType = value; }
    void setValue( BsObject * value ){ m_value = value; }
    void setvar( BsVariable * var ){ m_var = var; }
};


class BlockScript : public QObject
{
    Q_OBJECT
private:
    BsActionList m_actions;
public:
    explicit BlockScript(QObject *parent = 0);
    BsActionList actions(){ return m_actions; }
    void AddAction( BsAction * action ){ m_actions.append(action); }
    void AddActions( BsActionList actions ){ m_actions.append(actions); }
    void ClearActions() { m_actions.clear(); };
signals:

public slots:

};

#endif // BSSCRIPT_H
