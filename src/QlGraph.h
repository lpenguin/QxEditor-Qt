#ifndef QLGRAPH_H
#define QLGRAPH_H
#include "BaseGraph.h"
#include "QuestLogic.h"
#include "BlockScript.h"

class QlVerInfo : public BaseVerInfo{
Q_OBJECT
private:
    QlLocationTexts * m_locationTexts;
    BlockScript * m_actions;
public:
    QlVerInfo(  QString id, QObject * parent = 0 ):
        BaseVerInfo(id, parent){
        m_actions = new BlockScript();
        m_locationTexts = new QlLocationTexts();
    }

    QlVerInfo( QlLocationTexts * locationTexts, BlockScript * actions, VerType verType, QString id, QObject * parent = 0 ):
         BaseVerInfo(verType, id, parent){
        setLocationsText( locationTexts );
        setActions( actions );
    }

    void setLocationsText(QlLocationTexts * locationTexts ){
        SETPA( locationTexts )
    }
//    void setVerType(VerType verType){
//        m_verType = verType;
//    }
    void setActions( BlockScript * actions ){
        SETPA( actions )
    }

    QlLocationTexts * locationTexts( ) const{
        return m_locationTexts;
    }

    BlockScript * actions( ) const{
        return m_actions;
    }
//    ~QlVerInfo(){
//        delete m_locationTexts;
//        delete m_actions;
//    }

//    VerType verType( ) const{
//        return m_verType;
//    }
};

class QlEdgeInfo : public BaseEdgeInfo{
Q_OBJECT
private:
    QString m_text;
    QString m_question;
    BsExpression * m_expression;
    BlockScript * m_actions;
    QlPathStatementList m_pathStatements;
public:
    QlEdgeInfo( QString id, QObject * parent = 0 )
        :BaseEdgeInfo(id, parent )
    {
        setExpression( new BsNull );
        setActions( new BlockScript );
    }


    QlEdgeInfo(QString text, QString question, BsExpression * expression, BlockScript * actions, QlPathStatementList pathStatements, QString id, QObject * parent = 0 )
        :m_text(text), m_question( question ), BaseEdgeInfo(id, parent){
        setExpression( expression );
        setActions( actions );
        setPathStatements( pathStatements );
    }

    void setText(QString text ){
        m_text = text;
    }

    void setQuestion( QString question ){
        m_question = question;
    }

    void setExpression( BsExpression * expression ){
        SETPA( expression )
    }

    void setActions( BlockScript * actions ){
        SETPA( actions )
    }

    BsExpression * expression() const {
        return m_expression;
    }

    QString question() const {
        return m_question;
    }

    QString text() const {
        return m_text;
    }

    BlockScript * actions( ) const{
        return m_actions;
    }

    QlPathStatementList pathStatements() const{
        return m_pathStatements;
    }

    void setPathStatements( QlPathStatementList pathStatements){
        SETLA( pathStatements )
    }
};

class QlGraphInfo : public BaseGraphInfo{
    Q_OBJECT
private:
    QlParametrList m_parametrList;
public:
    QlGraphInfo( QString name, QString description, QlParametrList parametrList, QString id, QObject * parent = 0 ):
        m_parametrList(parametrList), BaseGraphInfo(name, description, id, parent ){}

    QlParametrList parametrList() const{
        return m_parametrList;
    }

       void setParametrList( QlParametrList parametrList ){
        m_parametrList = parametrList;
    }
};

class QlGraph : public BaseGraph
{
public:
    QlGraph();
};

#endif // QLGRAPH_H
