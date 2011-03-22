#ifndef QUESTLOGIC_H
#define QUESTLOGIC_H


#include "BlockScript.h"
#include <QtCore>

class QlConstraint;
class QlTrigger;
class QlShowVariable;
class QlLocationTexts;
class QlParamStatement;
class QlParametr;

typedef QList<QlParamStatement *> QlParamStatementList;
typedef QList<QlParametr *> QlParametrList;

namespace QlType{
    enum _t{
        Constraint = BsObject::UserType + 1, Trigger, ShowVariable, BoundTrigger, ParamStatement, Parametr, LocationTexts
    };
}

class QlParamStatement : public BsStatement{
public:
    virtual int type() const{ return QlType::ParamStatement; }
};

class QlConstraint : public QlParamStatement{
private:
    BsVariable * m_var;
    BsExpression * m_min;
    BsExpression * m_max;
public:
    QlConstraint( BsVariable * var, BsExpression * min , BsExpression * max ){
        setVar( var );
        setMin( min );
        setMax( max );
    }

    void setVar(BsVariable * var){
        SETPA( var );
    }
    void setMin( BsExpression * min ){
        SETPA( min );
    }
    void setMax( BsExpression * max ){
        SETPA( max );
    }
    BsVariable * var() const { return m_var; }
    BsExpression * min() const { return m_min; }
    BsExpression * max() const { return m_max; }
    virtual int type() const{ return QlType::Constraint; }
};

class QlTrigger : public BsStatement{
private:
    BsVariable * m_var;
    BsIf * m_ifStatement;
public:
    QlTrigger( BsVariable * var , BsIf * if_){
        setVar( var );
        setIf( if_ );
    }
    void setVar(BsVariable * var){
        SETPA( var);
    }
    void setIf(BsIf * ifStatement ){
        SETPA( ifStatement );
    }
    BsVariable * var() const { return m_var; }
    BsIf * ifStatement() const { return m_ifStatement; }
    virtual int type() const{ return QlType::Trigger; }

};

class QlShowVariable : public QlParamStatement{
private:
    BsVariable * m_var;
    BsRangeList m_ranges;
    QStringList m_strings;
public:
    QlShowVariable( BsVariable * var, BsRangeList ranges, QStringList strings){
        setVar( var );
        setRanges( ranges );
        setStrings( strings );
    }

    void setVar(BsVariable * var){
        SETPA( var);
    }
    void setRanges( BsRangeList ranges ){
        SETLA( ranges );
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
    void setValue( BsValue * value){ SETPA(value); }
    void setVar(BsVariable * var){
        SETPA( var);
    }
    virtual int type() const{ return QlType::BoundTrigger; }

};

class QlLocationTexts : public BsStatement{
private:
    QStringList m_texts;
    BsExpression * m_expr;
public:
    QString firstText() const{
        if( m_texts.count() )
            return m_texts[0];
        else return QString("");
    }
    QlLocationTexts( QStringList texts = QStringList (), BsExpression * expr = new BsNull ){
        setTexts( texts );
//        if(! expr )
//            expr = new BsExpression();
        setExpr( expr );
    }

    void setTexts( QStringList texts){
        m_texts = texts;
    }

    QStringList texts() const {
        return m_texts;
    }

    void setExpr( BsExpression * expr ){
        SETPA( expr);
    }

    BsExpression * expr() const{
        return m_expr;
    }

    int type() const {
        return QlType::LocationTexts;
    }

};

class QlParametr : public BsStatement{
private:
    BsVariable * m_var;
    QlParamStatementList m_paramStatements;
//    void setList( QlParamStatementList & list, QlParamStatementList value );

//    void add( QlParamStatementList & list, QlParamStatement * value);
public:
    QlParametr( BsVariable * var, QlParamStatementList paramStatements = QlParamStatementList()):
        m_var(var){
        setParamStatements( paramStatements );
    }

    QlParamStatementList paramStatements() const{
        return m_paramStatements;
    }

    BsVariable * var() const { return m_var; }

    void setVar(BsVariable * var){
        m_var = var;
    }

    void setParamStatements( QlParamStatementList paramStatements ){
        SETLA( paramStatements );
    }

    int type() const {
        return QlType::Parametr;
    }
};

#endif // QUESTLOGIC_H
