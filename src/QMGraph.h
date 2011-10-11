#ifndef QMGRAPH_H
#define QMGRAPH_H

#include <QtCore>

namespace QMScript{
class QMException;
struct QMAction;
struct QMLocation;
struct QMCondition;
struct QMPath;
struct QMParametrRange;
struct QMParametr;
struct QMStringReplaces;

typedef QList<QMAction*> QMActionList;
typedef QList<QMCondition*> QMConditionList;
typedef QList<QMPath*> QMPathList;
typedef QList<QMLocation*> QMLocationList;
typedef QList<QMParametr*> QMParametrList;
typedef QList<QMParametrRange> QMParametrRangeList;

class QMException: std::exception{
private:
    QString m_error;
public:
    QMException( QString error = QString::null ){
        m_error = error;
    }
    const char* what()  const throw(){
        return m_error.toAscii();
    }
    QMException( const QMException & e){
        m_error = e.m_error;
    }
    QMException & operator=( const QMException & e) {
        m_error = e.m_error;
        return *this;
    }
    ~QMException()throw() {  }
};

struct QMLocation{
    enum QMLocationType{
        Odinary, Start, Success, Fail, Death, Empty
    };

    qint32 x, y;
    QStringList texts;
    QString textFormula;
    bool selectTextByFormula;
    bool incDay;
    qint32 locNumber;
    QMLocationType type;
    QMActionList actions;
};

struct QMPath{
    qreal priority;
    bool incDay;
    qint32 pathNumber;
    QMLocation * ownerLoc;
    QMLocation *  nextLoc;
    bool alwaysShow;
    qint32 prohodimost;
    qint32 showOrder;
    QString logicalCondition;
    QString question, text;
    QMConditionList conditions;
    QMActionList actions;
};
struct QMParametr{
    enum QMParametrType{
        Odinary = 0, Fail = 1, Success = 2, Death = 3
    };
    enum QMCritValue{
        Max = 0, Min = 1
    };

    qint32 parNumber;
    QMParametrRangeList ranges;
    qint32 min, max;
    QString start;
    QMParametrType type;
    bool showOnZero;
    QMCritValue critValue;
    bool active;
    qint32 numStrings;
    bool isMoney;
    QString name;
    QString critText;
};

struct QMCondition{
    QMParametr * param;
    QList<qint32> equals;
    QList<qint32> kraten;
    bool isEquals, isKraten;
    qint32 maxDiap, minDiap;
    bool notEmpty(){
        if( !param )
            return false;
        qint32 min = param->min, max = param->max;
        if( param->type != QMParametr::Odinary ){
            if( param->critValue == QMParametr::Max )
                max--;
            if( param->critValue == QMParametr::Min )
                min++;
        }
        return isEquals || isKraten ||  maxDiap != max || minDiap != min  ;
    }
};
struct QMAction{
    enum QMParametrActionType{
        Number, Procent, Mov, Equation
    };
    enum QMParamterVisible{
        DontTouch, Show, Hide
    };
    QMParametr * param;
    //    QString parName;
    qint32 addNumber;
    QMParametrActionType type;

    QString equation;
    QMParamterVisible show;
    bool notEmpty(){
        return !( addNumber == 0 && equation.isEmpty() && show == QMAction::DontTouch && type != Mov);
    }
};


struct QMParametrRange{
    qint32 min, max;
    QString text;
};

struct QMStringReplaces{
    QString date;
    QString money;
    QString fromPlanet;
    QString fromStar;
    QString toPlanet;
    QString toStar;
    QString ranger;
    QString congString;
    QString missionString;
    QString distance;
    QString artefact;
};

class QMGraph
{
private:
    QMParametrList m_params;
    QMStringReplaces m_stringReplaces;
    QMLocationList m_locations;
    QMPathList m_paths;
public:
    QMGraph(QMParametrList params, QMLocationList locations, QMPathList paths , QMStringReplaces stringReplaces);
    QMParametrList params() const { return m_params; };
    QMStringReplaces stringReplaces() const { return m_stringReplaces; }
    QMLocationList locations() const { return m_locations; }
    QMPathList paths() const { return m_paths; }
};
}
#endif // QMGRAPH_H
