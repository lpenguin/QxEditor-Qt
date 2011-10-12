#ifndef QMSCRIPTTOBSCONVERTER_H
#define QMSCRIPTTOBSCONVERTER_H
#include "BlockScript.h"
#include "QuestLogic.h"
#include "QMReader.h"
#include "Transliter.h"
#include "Error.h"

#include <QtCore>
#include <QInputDialog>

#include "QmEqToBsConverter.h"
#include "BsToESMAScriptConverter.h"
#include "stringoper.h"

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
    BsExpression * ConvertQMLocaigalCondition( QString condition );
    BsExpression * ConvertQMEquation(QString equation);
    BsExpression * ConvertQMConditions( QMConditionList qmConditions );
    QString ConvertQMEquationsInText(const QString & text );
private:
    BsVariable * ConvertQMParametrToVariable( QMParametr * qmParametr);
    BsStatementList ConvertQMAction( QMAction * qmAction );

    BsConditionList ConvertQMCondition( QMCondition * qmCondition );
    BsRangeList ConvertQMRanges( QMParametrRangeList ranges );
    QStringList ConvertQMRangesTexts( QMParametrRangeList ranges, const QString & varName );
    QString ConvertQMParametrType(QMParametr::QMParametrType type);

    QmEqToBsConverter m_eqConverter;
    BsToESMAScriptConverter m_bsConverter;
};

#endif // QMSCRIPTTOBSCONVERTER_H
