#ifndef QUESTLOGIC_H
#define QUESTLOGIC_H


#include "BlockScript.h"
#include <QtCore>

class QlConstraint;
class QlTrigger;
class QlShowVariable;
class QlLocationTexts;
class QlParamStatement;

typedef QList<QlParamStatement> QlParamStatementList;

namespace QlType{
    enum _t{
        Constraint = BsObject::UserType + 1, Trigger, ShowVariable, BoundTrigger
    };
}

class QlParamStatement : public BsStatement{

};

class QlConstraint : public QlParamStatement{
private:
    BsVariable * m_var;
    BsExpression * m_min;
    BsExpression * m_max;
public:
    QlConstraint( BsVariable * var = 0, BsExpression * min = 0, BsExpression * max = 0){
        setVar( var );
        setMin( min );
        setMax( max );
    }

    void setVar(BsVariable * var){
        set( (BsObjectP&)m_var, (BsObjectP)var);
    }
    void setMin( BsExpression * min ){
        set( (BsObjectP&)m_min, (BsObjectP)min);
    }
    void setMax( BsExpression * max ){
        set( (BsObjectP&)m_max, (BsObjectP)max);
    }
    BsVariable * var() const { return m_var; }
    BsExpression * min() const { return m_min; }
    BsExpression * max() const { return m_max; }
    virtual int type() const{ return QlType::Constraint; }
};

class QlTrigger : public BsStatement{
private:
    BsVariable * m_var;
    BsIf * m_if;
public:
    QlTrigger( BsVariable * var = 0, BsIf * if_ = 0){
        setVar( var );
        setIf( if_ );
    }
    void setVar(BsVariable * var){
        set( (BsObjectP&)m_var, (BsObjectP)var);
    }
    void setIf(BsIf * if_){
        set( (BsObjectP&)m_if, (BsObjectP)if_);
    }
    BsVariable * var() const { return m_var; }
    BsIf * if_() const { return m_if; }
    virtual int type() const{ return QlType::Trigger; }

};

class QlShowVariable : public QlParamStatement{
private:
    BsVariable * m_var;
    BsRangeList m_ranges;
    QStringList m_strings;
public:
    QlShowVariable( BsVariable * var = 0, BsRangeList ranges = BsRangeList(), QStringList strings = QStringList()){
        setVar( var );
        setRanges( ranges );
        setStrings( strings );
    }

    void setVar(BsVariable * var){
        set( (BsObjectP&)m_var, (BsObjectP)var);
    }
    void setRanges( BsRangeList ranges ){
        setList( m_ranges, ranges );
    }
    void setStrings(QStringList strings ){
        m_strings = strings;
    }

    BsVariable * var() const { return m_var; }
    BsRangeList ranges() const { return m_ranges; }
    QStringList strings() const { return m_strings; }
    virtual int type() const{ return QlType::ShowVariable; }
};

class QlBoundTrigger : public QlParamStatement{
public:
    enum BoundType{
        Min, Max
    };
private:
    BsVariable * m_var;
    BoundType m_Boundtype;
    BsValue * m_value;
    QString m_text;
public:
    BoundType boundType() const{ return m_Boundtype; }
    BsValue * value() const {return m_value;}
    QString text()const {return m_text;}
    BsVariable * var() const { return m_var; }
    void setBoundType( BoundType boundType ){ m_Boundtype = boundType;}
    void setText( QString text ){ m_text = text;}
    void setValue( BsValue * value){ set((BsObjectP&) m_value, (BsObjectP)value); }
    void setVar(BsVariable * var){
        set( (BsObjectP&)m_var, (BsObjectP)var);
    }
    virtual int type() const{ return QlType::BoundTrigger; }

};

class QlParametr : public BsStatement{
private:
    BsVariable * m_var;
    QlParamStatementList m_patramStatements;

};

#endif // QUESTLOGIC_H
