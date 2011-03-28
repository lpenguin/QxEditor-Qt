#ifndef QLGRAPH_H
#define QLGRAPH_H
#include "BaseGraph.h"
#include "QuestLogic.h"
#include "BlockScript.h"

using namespace BlockScript;
namespace Graphs {
class QlVerInfo : public VerInfo{
Q_OBJECT
private:
    QlLocationStatementList m_locationStatements;
    BsScript * m_actions;
    QString m_text;
public:
    QlVerInfo(  QString id = QString(), QObject * parent = 0 ):
        VerInfo(id, parent){
        m_actions = new BsScript();
        m_text = QString();
    }

    QlVerInfo(QString text, QlLocationStatementList locationStatements, BsScript * actions, VerType verType, QString id, QObject * parent = 0 ):
         m_text(text),
         VerInfo(verType, id, parent){
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
    void setActions( BsScript * actions ){
        SETPA( actions )
    }

    QlLocationStatementList locationStatements( ) const{
        return m_locationStatements;
    }

    BsScript * actions( ) const{
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

class QlEdgeInfo : public EdgeInfo{
Q_OBJECT
private:
    QString m_text;
    QString m_question;
    BsExpression * m_expression;
    BsScript * m_actions;
    QlPathStatementList m_pathStatements;
public:
    QlEdgeInfo( QString id = QString(), QObject * parent = 0 )
        :EdgeInfo(id, parent )
    {
        setExpression( new BsNull );
        setActions( new BsScript );
    }


    QlEdgeInfo(QString text, QString question, BsExpression * expression, BsScript * actions, QlPathStatementList pathStatements, QString id, QObject * parent = 0 )
        :m_text(text), m_question( question ), EdgeInfo(id, parent){
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

    void setActions( BsScript * actions ){
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

    BsScript * actions( ) const{
        return m_actions;
    }

    QlPathStatementList pathStatements() const{
        return m_pathStatements;
    }

    void setPathStatements( QlPathStatementList pathStatements){
        SETLA( pathStatements )
    }
};

class QlGraphInfo : public GraphInfo{
    Q_OBJECT
private:
    QlParametrList m_parametrList;
    BsScript * m_actions;
public:
    QlGraphInfo( QString name = QString(), QString description = QString(), QStringList libraries = QStringList(),  QString id = QString(), QObject * parent = 0 ):
        GraphInfo(name, description, libraries, id, parent ){}
    QlGraphInfo( QString name, QString description, QStringList libraries, BsScript * actions, QlParametrList parametrList, QString id, QObject * parent = 0 ):
        GraphInfo(name, description, libraries, id, parent ){
        setParametrList( parametrList );
        setActions( actions );
    }

    QlParametrList parametrList() const{
        return m_parametrList;
    }

    void setParametrList( QlParametrList parametrList ){
        SETLA( parametrList );
    }

    BsScript * actions() const{
        return m_actions;
    }
    void setActions( BsScript * actions ){
        SETPA( actions )
    }
    virtual int tp() const {return 2; }
};

class QlGraph : public Graph
{
public:
    QlGraph();
};

}
#endif // QLGRAPH_H
