#ifndef SIMPLEGRAPH_H
#define SIMPLEGRAPH_H

#include <QString>
#include "BaseGraph.h"


class SimpleVerInfo : public BaseInfo {
private:
    QString m_actions;
    QString m_text;
    LocationType m_type;
public:
    SimpleVerInfo( QString id, QString actions, QString text, LocationType type, QObject * parent = 0 ):
        BaseInfo(id, parent), m_actions(actions), m_text(text), m_type(type) { setId(id); }

    SimpleVerInfo(){}
    void setActions( QString actions ){
        m_actions = actions;
    }

    void setText(QString text ){
        m_text = text;
    }

    void setType( LocationType type ){
        m_type = type;
    }

    QString actions() const{
        return m_actions;
    }

    LocationType type() const {
        return m_type;
    }
    QString text() const {
        return m_text;
    }
};

class SimpleEdgeInfo : public BaseInfo{
private:
        QString m_actions;
        QString m_conditions;
        QString m_text;
        QString m_question;
public:
        SimpleEdgeInfo( QString id, QString actions, QString conditions, QString text, QString question, QObject * parent = 0 ):
            BaseInfo(id, parent), m_actions(actions), m_text(text), m_conditions(conditions), m_question(question)
            {}
        SimpleEdgeInfo(){};

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
            return m_actions;
        }
        QString question() const{
            return m_question;
        }

        QString text() const{
            return m_text;
        }
};

class SimpleGraphInfo : public BaseInfo{
private:
    QString m_actions;
    QString m_name;
    QString m_description;
public:
    SimpleGraphInfo(  QString name, QString description, QString actions, QString id = QString::null, QObject * parent =0):
    BaseInfo(id, parent), m_name(name), m_description(description), m_actions(actions){}

    QString actions() const{
        return m_actions;
    }

    void setActions( QString actions ){
        m_actions = actions;
    }

    void setName( QString name ){
        m_name = name;
    }
    QString name() const{
        return m_name;
    }

    void setDescription( QString description ){
        m_description = description;
    }
    QString description() const{
        return m_description;
    }

};

//graph->setScript( sc.property("actions").toString());
//graph->setName( sc.property("name").toString());
//graph->setDescription( sc.property("description").toString());

class SimpleGraph : public BaseGraph
{
    Q_OBJECT
private:
    QString m_script;
    QString m_name;
    QString m_description;
public:
    explicit SimpleGraph(QObject *parent = 0);

    void setScript( QString value) { m_script = value; }
    QString name( void ){ return m_name;}
    void setName( QString value ){ m_name = value; }
    QString description( void ){ return m_description; }
    void setDescription( QString value ){ m_description = value; }
    QString script() { return m_script; }

};

#endif // SIMPLEGRAPH_H
