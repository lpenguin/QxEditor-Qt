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
    QlVerInfo( QlLocationTexts * locationTexts, BlockScript * actions, VerType verType, QString id, QObject * parent = 0 ):
        m_locationTexts(locationTexts), m_actions(actions), BaseVerInfo(verType, id, parent){}

    void setLocationsText(QlLocationTexts * locationTexts ){
        m_locationTexts = locationTexts;
    }
//    void setVerType(VerType verType){
//        m_verType = verType;
//    }
    void setActions( BlockScript * actions ){
        m_actions = actions;
    }

    QlLocationTexts * locationTexts( ) const{
        return m_locationTexts;
    }

    BlockScript * actions( ) const{
        return m_actions;
    }

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
public:
    QlEdgeInfo(QString text, QString question, BsExpression * expression, BlockScript * actions, QString id, QObject * parent = 0 )
        :m_text(text), m_question( question ), m_expression( expression), m_actions( actions ), BaseEdgeInfo(id, parent){}

    void setText(QString text ){
        m_text = text;
    }

    void setQuestion( QString question ){
        m_question = question;
    }

    void setExpression( BsExpression * expression ){
        m_expression = expression;
    }

    void setActions( BlockScript * actions ){
        m_actions = actions;
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
};

class QlGraphInfo : public BaseGraphInfo{
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
