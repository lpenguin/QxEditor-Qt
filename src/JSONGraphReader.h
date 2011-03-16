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
    virtual BaseInfo * ReadVerInfo( QScriptValue value ) = 0;
    virtual BaseInfo * ReadEdgeInfo( QScriptValue value ) = 0;
    virtual BaseInfo * ReadGraphInfo( QScriptValue value ) = 0;
};

class SimpleJSONInfoReader : public AbstractJSONInfoReader{
public:
    BaseInfo * ReadVerInfo( QScriptValue value );
    BaseInfo * ReadEdgeInfo(  QScriptValue value );
    BaseInfo * ReadGraphInfo( QScriptValue value );
};

class JSONGraphReader : public AbstractGraphReader
{
public:
    JSONGraphReader( AbstractJSONInfoReader * infoReader = 0);
    virtual BaseGraph * ReadGraph(const QString & filename, BaseGraph * graph = 0);
    virtual int type() const { return JSONGraphReaderType; };
private:
    BaseVer * LoadVer( QScriptValue value );
    void LoadVers( BaseGraph * graph, QScriptValue value );
    void LoadEdges( BaseGraph * graph, QScriptValue value );
    BaseEdge * LoadEdge( BaseGraph * graph, QScriptValue value, BaseVer * ver);
};

#endif // JSONGRAPHREADER_H
