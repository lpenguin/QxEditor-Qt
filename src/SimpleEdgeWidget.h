#ifndef SIMPLEEDGEWIDGET_H
#define SIMPLEEDGEWIDGET_H

#include <QWidget>
#include "BaseWidgets.h"
#include "BaseGraph.h"
#include "SimpleGraph.h"

namespace Ui {
    class SimpleEdgeWidget;
}

class SimpleEdgeWidget : public BaseEdgeWidget
{
    Q_OBJECT

public:
    explicit SimpleEdgeWidget(QWidget *parent = 0);
    ~SimpleEdgeWidget();
    void ShowEdge(BaseEdge *edge);
    void WriteEdge(BaseEdge *edge);
private:
    Ui::SimpleEdgeWidget *ui;
};

#endif // SIMPLEEDGEWIDGET_H
