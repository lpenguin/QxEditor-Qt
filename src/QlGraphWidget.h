#ifndef QLGRAPHWIDGET_H
#define QLGRAPHWIDGET_H

#include <QWidget>
#include "BaseWidgets.h"
#include "BaseGraph.h"
#include "QlGraph.h"
#include "BsToESMAScriptConverter.h"
#include "ECMAScriptToBsConverter.h"

namespace Ui {
    class QlGraphWidget;
}

class QlGraphWidget : public BaseGraphWidget
{
    Q_OBJECT

public:
    explicit QlGraphWidget(QWidget *parent = 0);
    ~QlGraphWidget();
    void ShowGraph(Graph *graph);
    void WriteGraph(Graph *graph);
private:
    Ui::QlGraphWidget *ui;
    BsToESMAScriptConverter m_bsToEsConverter;
    ECMAScriptToBsConverter m_esToBsConverter;
};

#endif // QLGRAPHWIDGET_H
