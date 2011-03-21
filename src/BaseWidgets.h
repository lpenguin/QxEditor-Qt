#ifndef BASEWIDGETS_H
#define BASEWIDGETS_H

#include <QWidget>
#include "BaseGraph.h"

class BaseEdgeWidget : public QWidget
{
    Q_OBJECT
public:
    explicit BaseEdgeWidget(QWidget *parent = 0):QWidget(parent){}
    virtual void ShowEdge( BaseEdge * edge ){};
    virtual void WriteEdge( BaseEdge * edge ){};
signals:

public slots:

};

class BaseVerWidget : public QWidget
{
    Q_OBJECT
public:
    explicit BaseVerWidget(QWidget *parent = 0):QWidget(parent){}
    virtual void ShowVer( BaseVer * ver ){}
    virtual void WriteVer( BaseVer * ver ){}
signals:

public slots:

};

#endif // BASEWIDGETS_H
