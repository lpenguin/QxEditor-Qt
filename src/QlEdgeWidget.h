#ifndef QLEDGEWIDGET_H
#define QLEDGEWIDGET_H

#include <QWidget>
#include "BaseWidgets.h"
#include "BaseGraph.h"
#include "QlGraph.h"
#include "BsToESMAScriptConverter.h"
#include "ECMAScriptToBsConverter.h"

namespace Ui {
    class QlEdgeWidget;
}

class QlEdgeWidget : public BaseEdgeWidget
{
    Q_OBJECT

public:
    explicit QlEdgeWidget(QWidget *parent = 0);
    ~QlEdgeWidget();
    void ShowEdge(Edge *edge);
    void WriteEdge(Edge *edge);
private:
    Ui::QlEdgeWidget *ui;
    BsToESMAScriptConverter * m_bsToEsConverter;
    ECMAScriptToBsConverter * m_esToBsConverter;
};

#endif // QLEDGEWIDGET_H
