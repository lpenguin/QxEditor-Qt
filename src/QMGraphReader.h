#ifndef QMGRAPHREADER_H
#define QMGRAPHREADER_H

#include "AbstractGraphReader.h"
#include "Graph.h"
#include <QFile>
#include <QString>
#include "MyDataStream.h"
#include <iostream>
class QMException;
struct QMAction;
struct QMLocation;
struct QMCondition;
struct QMPath;
struct QMParametrRange;
struct QMParametr;
struct QMStringReplaces;

struct QMAction{
    enum QMParametrActionType{
            Number, Procent, Mov, Equation
    };
    enum QMParamterVisible{
            DontTouch, Show, Hide
    };
    QMParametr * param;
    QString parName;
    qint32 addNumber;
    QMParametrActionType type;

    QString equation;
    QMParamterVisible show;
    bool notEmpty(){
                return !(addNumber == 0 && equation.isEmpty() && show == QMAction::DontTouch);
    }
};

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
    QList<QMAction> actions;
};

struct QMCondition{
    QString parName;
    QMParametr * param;
    QList<qint32> equals;
    QList<qint32> kraten;
    bool isEquals, isKraten;
    qint32 maxDiap, minDiap;
    bool notEmpty(){
        return isEquals || isKraten;
    }
};

struct QMPath{
    qreal priority;
    bool incDay;
    qint32 pathNumber;
    qint32 ownerLocNumber;
    qint32 nextLocNumber;
    bool alwaysShow;
    qint32 prohodimost;
    qint32 showOrder;
    QString logicalCondition;
    QString question, text;
    QList<QMCondition> conditions;
    QList<QMAction> actions;
};

struct QMParametrRange{
    qint32 min, max;
    QString text;
};

struct QMParametr{
    enum QMParametrType{
        Odinary = 0, Fail = 1, Success = 2, Death = 3
    };
    enum QMCritValue{
        Max = 0, Min = 1
    };

    qint32 parNumber;
    QList<QMParametrRange> ranges;
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

struct QMStringReplaces{
     QString date;
     QString money;
     QString fromPlanet;
     QString fromStar;
     QString toPlanet;
     QString toStar;
     QString ranger;
};

class QMGraphReader : public AbstractGraphReader
{
public:
    QMGraphReader(qint32 paramsCount = 32);
    Graph * ReadGraph(const QString & filename, Graph * graph = 0);
private:
    qint32 paramsCount;
    QList<QMParametr> m_params;
    QString m_errorString;
    QMStringReplaces m_stringReplaces;
    QString m_congString;
    QString m_missionString;
    QList<QMLocation> m_locations;
    QList<QMPath> m_paths;

    QMAction ReadActionFromLocaion(  MyDataStream & stream, qint32 paramNumber);
    QMAction ReadActionFromPath(MyDataStream &br, qint32 paramNumber);
    QMCondition ReadCondition( MyDataStream &br, qint32 paramNumber);
    QMParametr ReadParametr( MyDataStream & stream );
    QMPath ReadPath( MyDataStream & stream );
    QMLocation ReadLocation( MyDataStream & stream );

    QMAction::QMParametrActionType ReadActionType( MyDataStream & stream );
    QMLocation::QMLocationType ReadLocationType( MyDataStream & stream );
    QMParametrRange ReadParametrRange( MyDataStream & stream );
    QMAction::QMParamterVisible IntToQMParamterVisible(qint32 vis);
    QMParametr::QMCritValue IntToQMCritValue(int critVal);
    QMParametr::QMParametrType IntToQMParametrType(int type);


};

#endif // QMGRAPHREADER_H
