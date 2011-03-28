#ifndef QUESTLOGIC_H
#define QUESTLOGIC_H


#include "BlockScript.h"
#include <QtCore>

using namespace BlockScript;
namespace QlType{
    enum _t{
        Constraint = BsObject::UserType + 1, Trigger, ShowVariable, BoundTrigger, ParamStatement, Parametr, LocationTexts, PathPriority, PathPassability, PathShowOrder
    };
}

namespace BlockScript{
class QlConstraint;
class QlTrigger;
class QlShowVariable;
class QlLocationTexts;
class QlParamStatement;
class QlParametr;
class QlPathStatement;
class QlLocationStatement ;

typedef QList<QlParamStatement *> QlParamStatementList;
typedef QList<QlParametr *> QlParametrList;
typedef QList<QlPathStatement * > QlPathStatementList;
typedef QList<QlLocationStatement * > QlLocationStatementList;



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

class QlTrigger : public BsIf{
//private:
//    BsVariable * m_var;
//    BsIf * m_ifStatement;
//public:
//    QlTrigger( BsVariable * var , BsIf * if_){
//        setVar( var );
//        setIf( if_ );
//    }
//    void setVar(BsVariable * var){
//        SETPA( var);
//    }
//    void setIf(BsIf * ifStatement ){
//        SETPA( ifStatement );
//    }
//    BsVariable * var() const { return m_var; }
//    BsIf * ifStatement() const { return m_ifStatement; }
public:
    QlTrigger( BsExpression * expression, BsStatementList statements):
        BsIf(expression, statements){}
    virtual int type() const{ return QlType::Trigger; }

};

class QlShowVariable : public QlParamStatement{
private:
    BsVariable * m_var;
    BsRangeList m_ranges;
    QStringList m_strings;
    bool m_showOnZero;
public:
    QlShowVariable( BsVariable * var, BsRangeList ranges, QStringList strings, bool showOnZero = true){
        setVar( var );
        setRanges( ranges );
        setStrings( strings );
        setShowOnZero( showOnZero );
    }

    bool showOnZero(){
        return m_showOnZero;
    }

    void setShowOnZero( bool showOnZero ){
        m_showOnZero = showOnZero;
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
    BoundType m_boundtype;
    BsValue * m_value;
    QString m_text;
public:
    QlBoundTrigger( BsVariable * var, BsValue * value, BoundType boundtype, QString text){
        setVar( var );
        setValue( value );
        setBoundType( boundtype );
        setText( text );
    }
    QlBoundTrigger(){

    }

    BoundType boundType() const{ return m_boundtype; }
    BsValue * value() const {return m_value;}
    QString text()const {return m_text;}
    BsVariable * var() const { return m_var; }
    void setBoundType( BoundType boundType ){ m_boundtype = boundType;}
    void setText( QString text ){ m_text = text;}
    void setValue( BsValue * value){ SETPA(value); }
    void setVar(BsVariable * var){
        SETPA( var);
    }
    virtual int type() const{ return QlType::BoundTrigger; }

};

class QlLocationStatement : public BsStatement {
private:
    QString m_locationId;
public:
    QlLocationStatement( QString locationId = QString() ):
        m_locationId(locationId){}
    QString locationId() const{
        return m_locationId;
    }

    void setLocationId( QString locationId ){
        m_locationId = locationId;
    }
};

class QlLocationTexts : public QlLocationStatement{
private:
    QStringList m_texts;
    BsExpression * m_expr;
public:


    QlLocationTexts( QString locationId = QString(), QStringList texts = QStringList (), BsExpression * expr = new BsNull ):
        QlLocationStatement( locationId )
    {
        setTexts( texts );
//        if(! expr )
//            expr = new BsExpression();
        setExpr( expr );
    }

    QString firstText() const{
        if( m_texts.count() )
            return m_texts[0];
        else return QString("");
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
    BsExpression * m_startValue;
    QlParamStatementList m_paramStatements;
//    void setList( QlParamStatementList & list, QlParamStatementList value );

//    void add( QlParamStatementList & list, QlParamStatement * value);
public:
    QlParametr( BsVariable * var, BsExpression * startValue, QlParamStatementList paramStatements = QlParamStatementList())
    {
        setParamStatements( paramStatements );
        setVar( var );
        setStartValue( startValue );
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

    BsExpression * startValue() const {
        return m_startValue;
    }

    void setStartValue( BsExpression * startValue ){
        SETPA( startValue )
    }

    int type() const {
        return QlType::Parametr;
    }
};

class QlPathStatement : public BsStatement{
private:
    QString m_pathId;
public:
    QlPathStatement( QString pathId = QString() ):
        m_pathId(pathId){}
    QString pathId() const{
        return m_pathId;
    }

    void setPathId( QString pathId ){
        m_pathId = pathId;
    }
};

class QlPathPriority : public QlPathStatement{
private:
    qreal m_priority;
public:
    QlPathPriority( QString pathId  = QString(), qreal priority = 0):
        QlPathStatement( pathId ), m_priority( priority ){}

    qreal priority() const{
        return m_priority;
    }

    void setPriority( qreal priority ){
        m_priority = priority;
    }
    virtual int type() const{
        return QlType::PathPriority;
    }
};

class QlPathShowOrder : public QlPathStatement{
private:
    qint32 m_showOrder;
public:
    QlPathShowOrder( QString pathId  = QString(),  qint32 showOrder = 0):
        QlPathStatement( pathId ), m_showOrder( showOrder ){}

    qint32 showOrder() const{
        return m_showOrder;
    }

    void setShowOrder( qreal showOrder ){
        m_showOrder = showOrder;
    }
    virtual int type() const{
        return QlType::PathShowOrder;
    }
};

class QlPathPassability : public QlPathStatement{
private:
    qint32 m_passability;
public:
    QlPathPassability( QString pathId,  qint32 passability = 0):
        QlPathStatement( pathId ), m_passability( passability ){}

    qint32 passability() const{
        return m_passability;
    }

    void setPassability( qreal passability ){
        m_passability = passability;
    }
    virtual int type() const{
        return QlType::PathPassability;
    }
};
}
#endif // QUESTLOGIC_H
