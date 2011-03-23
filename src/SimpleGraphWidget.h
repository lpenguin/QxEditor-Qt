#ifndef SIMPLEGRAPHWIDGET_H
#define SIMPLEGRAPHWIDGET_H

#include <QWidget>
#include "BaseWidgets.h"
#include "BaseGraph.h"
#include "SimpleGraph.h"

namespace Ui {
    class SimpleGraphWidget;
}

class SimpleGraphWidget : public BaseGraphWidget
{
    Q_OBJECT

public:
    explicit SimpleGraphWidget(QWidget *parent = 0);
    ~SimpleGraphWidget();
    void ShowGraph(BaseGraph *graph);
    void WriteGraph(BaseGraph *graph);

private:
    Ui::SimpleGraphWidget *ui;
};

#endif // SIMPLEGRAPHWIDGET_H
