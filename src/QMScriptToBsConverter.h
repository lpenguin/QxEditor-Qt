#ifndef QMSCRIPTTOBSCONVERTER_H
#define QMSCRIPTTOBSCONVERTER_H
#include "BlockScript.h"
#include "QMReader.h"
#include "Transliter.h"

#include <QtCore>

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
    BsInstructionList ConvertInstructions( QMActionList qmActions);
    BsVariable * ConvertQMParametr( QMParametr * qmParametr);
    BsInstructionList ConvertInstruction( QMAction * qmAction );
    BsUserString * ConvertQMEquation(QString equation);
    BsConditionList ConvertQMCondition( QMCondition * qmCondition );
    BsConditionList ConvertQMConditions( QMConditionList qmConditions );
    BsCondition * ConvertQMLocaigalCondition( QString condition );
    void setQmGlobals( QMParametrList qmGlobals );
};

#endif // QMSCRIPTTOBSCONVERTER_H
