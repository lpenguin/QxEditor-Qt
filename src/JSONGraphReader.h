#ifndef JSONGRAPHREADER_H
#define JSONGRAPHREADER_H

#include "AbstractGraphReader.h"
#include "Graph.h"
#include <QtCore>
//#include <QScriptEngine>
#include <QtScript>
#include <QMessageBox>

enum eJSONGraphReaderType {
    JSONGraphReaderType = 1
};

class JSONGraphReader : public AbstractGraphReader
{
public:
    JSONGraphReader();
    virtual Graph * ReadGraph(const QString & filename, Graph * graph = 0);
    virtual int type() const { return JSONGraphReaderType; };
private:
    Ver * LoadVer( QScriptValue value );
    void LoadVers( Graph * graph, QScriptValue value );
    void LoadEdges( Graph * graph, QScriptValue value );
    Edge * LoadEdge( Graph * graph, QScriptValue value, Ver * ver);
};

#endif // JSONGRAPHREADER_H
