#ifndef QLGRAPH_H
#define QLGRAPH_H
#include "BaseGraph.h"
#include "QuestLogic.h"
#include "BlockScript.h"

class QlVerInfo : public BaseVerInfo{
Q_OBJECT
private:
    QlLocationStatementList m_locationStatements;
    BlockScript * m_actions;
    QString m_text;
public:
    QlVerInfo(  QString id = QString(), QObject * parent = 0 ):
        BaseVerInfo(id, parent){
        m_actions = new BlockScript();
        m_text = QString();
    }

    QlVerInfo(QString text, QlLocationStatementList locationStatements, BlockScript * actions, VerType verType, QString id, QObject * parent = 0 ):
         m_text(text),
         BaseVerInfo(verType, id, parent){
        setLocationStatements( locationStatements );
        setActions( actions );
    }

//    QString firstText() {
//        foreach( QlLocationStatement * st, m_locationStatements ){
//            if( st->type() == QlType::LocationTexts ){
//                QlLocationTexts * texts = (QlLocationTexts*) st;
//                return texts->firstText();
//            }
//            return QString();
//        }
//    }

    QString text() const{
        return m_text;
    }

    void setText( QString text ){
        m_text = text;
    }

    void setLocationStatements( QlLocationStatementList locationStatements ){
        SETLA( locationStatements )
    }
//    void setVerType(VerType verType){
//        m_verType = verType;
//    }
    void setActions( BlockScript * actions ){
        SETPA( actions )
    }

    QlLocationStatementList locationStatements( ) const{
        return m_locationStatements;
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
    QlEdgeInfo( QString id = QString(), QObject * parent = 0 )
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
    BlockScript * m_actions;
public:
    QlGraphInfo( QString name = QString(), QString description = QString(), QString id = QString(), QObject * parent = 0 ):
        BaseGraphInfo(name, description, id, parent ){}
    QlGraphInfo( QString name, QString description, BlockScript * actions, QlParametrList parametrList, QString id, QObject * parent = 0 ):
        BaseGraphInfo(name, description, id, parent ){
        setParametrList( parametrList );
        setActions( actions );
    }

    QlParametrList parametrList() const{
        return m_parametrList;
    }

    void setParametrList( QlParametrList parametrList ){
        SETLA( parametrList );
    }

    BlockScript * actions() const{
        return m_actions;
    }
    void setActions( BlockScript * actions ){
        SETPA( actions )
    }
};

class QlGraph : public BaseGraph
{
public:
    QlGraph();
};

#endif // QLGRAPH_H
