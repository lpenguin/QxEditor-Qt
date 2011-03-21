#ifndef QLEDGEWIDGET_H
#define QLEDGEWIDGET_H

#include <QWidget>
#include "BaseWidgets.h"
#include "BaseGraph.h"
#include "QlGraph.h"
#include "BsToESMAScriptConverter.h"

namespace Ui {
    class QlEdgeWidget;
}

class QlEdgeWidget : public BaseEdgeWidget
{
    Q_OBJECT

public:
    explicit QlEdgeWidget(QWidget *parent = 0);
    ~QlEdgeWidget();
    void ShowEdge(BaseEdge *edge);
    void WriteEdge(BaseEdge *edge);
private:
    Ui::QlEdgeWidget *ui;
    BsToESMAScriptConverter * m_converter;
};

#endif // QLEDGEWIDGET_H
