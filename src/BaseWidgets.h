#ifndef BASEWIDGETS_H
#define BASEWIDGETS_H

#include <QWidget>
#include "BaseGraph.h"

using namespace Graphs;

class BaseEdgeWidget : public QWidget
{
    Q_OBJECT
public:
    explicit BaseEdgeWidget(QWidget *parent = 0):QWidget(parent){}
    virtual void ShowEdge( Edge * edge ){};
    virtual void WriteEdge( Edge * edge ){};
signals:

public slots:

};

class BaseVerWidget : public QWidget
{
    Q_OBJECT
public:
    explicit BaseVerWidget(QWidget *parent = 0):QWidget(parent){}
    virtual void ShowVer( Ver * ver ){}
    virtual void WriteVer( Ver * ver ){}
signals:

public slots:

};

class BaseGraphWidget : public QWidget
{
    Q_OBJECT
public:
    explicit BaseGraphWidget(QWidget *parent = 0):QWidget(parent){}
    virtual void ShowGraph( Graph * graph ){}
    virtual void WriteGraph( Graph * graph ){}
signals:

public slots:

};

#endif // BASEWIDGETS_H
