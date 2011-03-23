#ifndef QLGRAPHWIDGET_H
#define QLGRAPHWIDGET_H

#include <QWidget>
#include "BaseWidgets.h"
#include "BaseGraph.h"
#include "QlGraph.h"
#include "BsToESMAScriptConverter.h"
namespace Ui {
    class QlGraphWidget;
}

class QlGraphWidget : public BaseGraphWidget
{
    Q_OBJECT

public:
    explicit QlGraphWidget(QWidget *parent = 0);
    ~QlGraphWidget();
    void ShowGraph(BaseGraph *graph);
    void WriteGraph(BaseGraph *graph);
private:
    Ui::QlGraphWidget *ui;
    BsToESMAScriptConverter m_converter;
};

#endif // QLGRAPHWIDGET_H
