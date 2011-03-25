#ifndef JSONGRAPHWRITER_H
#define JSONGRAPHWRITER_H

#include "BaseGraph.h"
#include "AbstractGraphWriter.h"
#include <QtCore>
#include <QtScript>
#include "SimpleGraph.h"
//#include <parser.h>

QString Type2Str( SimpleVerInfo::VerType type );
QString Property2JSON(QString name, QString value);

class AbstractJSONInfoWriter{
public:
    virtual QStringList VerInfo2JSON( VerInfo * info ) = 0;
    virtual QStringList EdgeInfo2JSON( EdgeInfo * info ) = 0;
    virtual QStringList GraphInfo2JSON( GraphInfo * info ) = 0;
};

class SimpleJSONInfoWriter : public AbstractJSONInfoWriter{
public:
    virtual QStringList VerInfo2JSON( VerInfo * info );
    virtual QStringList EdgeInfo2JSON( EdgeInfo * info );
    virtual QStringList GraphInfo2JSON( GraphInfo * info );
};

class JSONGraphWriter : public AbstractGraphWriter
{
private:
    AbstractJSONInfoWriter * m_infoWriter;
public:
    JSONGraphWriter( AbstractJSONInfoWriter * infoWriter = 0 ):
        m_infoWriter( infoWriter ){}
    void setInfoWriter( AbstractJSONInfoWriter * infoWriter ){
        m_infoWriter = infoWriter;
    }

    AbstractJSONInfoWriter * infoWriter()const{
        return m_infoWriter;
    }

    virtual void WriteGraph( Graph * graph, const QString & filename );
    QString Edge2JSON(Edge * edge);
    QString Ver2JSON(Ver * ver);
};

#endif // JSONGRAPHWRITER_H
