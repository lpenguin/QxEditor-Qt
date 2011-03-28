#ifndef SIMPLEGRAPH_H
#define SIMPLEGRAPH_H

#include <QString>
#include "BaseGraph.h"

namespace Graphs{

class SimpleVerInfo : public VerInfo {
Q_OBJECT
private:
    QString m_actions;
    QString m_text;
public:
    SimpleVerInfo( QString id, QString actions, QString text, VerInfo::VerType type, QObject * parent = 0 ):
        VerInfo(type, id, parent), m_actions(actions), m_text(text){ }
    SimpleVerInfo( QString id, QObject * parent = 0 ):
        VerInfo(id, parent)
    {}
    SimpleVerInfo(){}
    void setActions( QString actions ){
        m_actions = actions;
    }

    void setText(QString text ){
        m_text = text;
    }

    QString actions() const{
        return m_actions;
    }

    QString text() const {
        return m_text;
    }
};

class SimpleEdgeInfo : public EdgeInfo{
private:
Q_OBJECT
        QString m_actions;
        QString m_conditions;
        QString m_text;
        QString m_question;
public:
        SimpleEdgeInfo( QString id, QString actions, QString conditions, QString text, QString question, QObject * parent = 0 ):
            EdgeInfo(id, parent), m_actions(actions), m_text(text), m_conditions(conditions), m_question(question)
            {}
        SimpleEdgeInfo(){};
        SimpleEdgeInfo( QString id, QObject * parent = 0):
            EdgeInfo(id, parent){}
        void setActions( QString actions ){
            m_actions = actions;
        }

        void setText(QString text ){
            m_text = text;
        }
        void setConditions(QString conditions ){
            m_conditions = conditions;
        }
        void setQuestion(QString question ){
            m_question = question;
        }
        QString actions() const{
            return m_actions;
        }

        QString conditions() const{
            return m_conditions;
        }
        QString question() const{
            return m_question;
        }

        QString text() const{
            return m_text;
        }
};

class SimpleGraphInfo : public GraphInfo{
    Q_OBJECT
private:
    QString m_actions;
public:
    SimpleGraphInfo(  QString name, QString description, QStringList libraries,  QString actions, QString id = QString::null, QObject * parent = 0):
        GraphInfo(name, description, libraries, id, parent), m_actions(actions){}
    SimpleGraphInfo( QString id = QString() , QObject * parent = 0):
        GraphInfo(id, parent)
    {
        m_actions = QString("");
    }
    QString actions() const{
        return m_actions;
    }

    void setActions( QString actions ){
        m_actions = actions;
    }
    virtual int tp() const {return 1; }
};

//graph->setScript( sc.property("actions").toString());
//graph->setName( sc.property("name").toString());
//graph->setDescription( sc.property("description").toString());

class SimpleGraph : public Graph
{
    Q_OBJECT
//private:
//    QString m_script;
public:
    explicit SimpleGraph(QObject *parent = 0);

//    void setScript( QString value) { m_script = value; }
//    QString name( void ){ return m_name;}
//    void setName( QString value ){ m_name = value; }
//    QString description( void ){ return m_description; }
//    void setDescription( QString value ){ m_description = value; }
//    QString script() { return m_script; }
};

}
#endif // SIMPLEGRAPH_H
