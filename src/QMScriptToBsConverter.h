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
    BlockScript ConvertActions( QMActionList actions);
    BsVariable * ConvertQMParametr( QMParametr * qmParametr);
    BsActionList ConvertAction( QMAction * qmAction );
    BsUserString * ConvertQMEquation(QString equation);
};

#endif // QMSCRIPTTOBSCONVERTER_H
