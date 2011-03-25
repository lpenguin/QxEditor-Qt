#ifndef QMSCRIPTTOBSCONVERTER_H
#define QMSCRIPTTOBSCONVERTER_H
#include "BlockScript.h"
#include "QuestLogic.h"
#include "QMReader.h"
#include "Transliter.h"
#include "Error.h"

#include <QtCore>

using namespace  BlockScript;

class QMScriptToBsConverter
{
private:
    QMParametrList m_qmGlobals;
    BsVariableList m_globals;
    QMap<QMParametr *, BsVariable *> m_varMap;
public:
    QMScriptToBsConverter(QMParametrList qmGlobals = QMParametrList() );

    BsVariableList globals(){ return m_globals; }
    QMParametrList qmGlobals(){ return m_qmGlobals; }
    void setQmGlobals( QMParametrList qmGlobals );

    BsScript * ConvertQMActions( QMActionList qmActions);
    QlParametr *  ConvertQMParametr( QMParametr * qmParametr);
    BsCondition * ConvertQMLocaigalCondition( QString condition );
    BsCondition * ConvertQMConditions( QMConditionList qmConditions );
private:
    BsVariable * ConvertQMParametrToVariable( QMParametr * qmParametr);
    BsStatementList ConvertQMAction( QMAction * qmAction );
    BsUserString * ConvertQMEquation(QString equation);
    BsConditionList ConvertQMCondition( QMCondition * qmCondition );
    BsRangeList ConvertQMRanges( QMParametrRangeList ranges );
    QStringList ConvertQMRangesTexts( QMParametrRangeList ranges );
    QString ConvertQMParametrType(QMParametr::QMParametrType type);


};

#endif // QMSCRIPTTOBSCONVERTER_H
