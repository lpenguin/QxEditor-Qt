#ifndef JSONGRAPHREADER_H
#define JSONGRAPHREADER_H

#include "AbstractGraphReader.h"
#include "BaseGraph.h"
#include "SimpleGraph.h"

#include <QtCore>
#include <QtScript>
#include <QMessageBox>

enum eJSONGraphReaderType {
    JSONGraphReaderType = 1
};

class AbstractJSONInfoReader{
public:
    virtual BaseVerInfo * ReadVerInfo( QScriptValue value ) = 0;
    virtual BaseEdgeInfo * ReadEdgeInfo( QScriptValue value ) = 0;
    virtual BaseGraphInfo * ReadGraphInfo( QScriptValue value ) = 0;
};

class SimpleJSONInfoReader : public AbstractJSONInfoReader{
public:
    BaseVerInfo * ReadVerInfo( QScriptValue value );
    BaseEdgeInfo * ReadEdgeInfo(  QScriptValue value );
    BaseGraphInfo * ReadGraphInfo( QScriptValue value );
};

class JSONGraphReader : public AbstractGraphReader
{
private:
    AbstractJSONInfoReader * m_infoReader;
public:
    JSONGraphReader( AbstractJSONInfoReader * infoReader = 0);
    virtual BaseGraph * ReadGraph(const QString & filename, BaseGraph * graph = 0);
    virtual int type() const { return JSONGraphReaderType; };
    void setInfoReader( AbstractJSONInfoReader * infoReader );
private:
    BaseVer * LoadVer( QScriptValue value );
    void LoadVers( BaseGraph * graph, QScriptValue value );
    void LoadEdges( BaseGraph * graph, QScriptValue value );
    BaseEdge * LoadEdge( BaseGraph * graph, QScriptValue value, BaseVer * ver);
};

#endif // JSONGRAPHREADER_H
