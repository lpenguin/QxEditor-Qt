#ifndef EDGEDIALOG_H
#define EDGEDIALOG_H

#include <QDialog>
#include "BaseGraph.h"
#include "BaseWidgets.h"

namespace Ui {
    class EdgeDialog;
}

class EdgeDialog : public QDialog
{
    Q_OBJECT

public:
    explicit EdgeDialog(QWidget *parent = 0);
    ~EdgeDialog();
    int ShowEdge(Edge * edge);
    void setEdgeWidget( BaseEdgeWidget * widget );
private:
    Ui::EdgeDialog *ui;
    Edge * m_edge;
public slots:
    void buttonboxAccepted();
};

#endif // EDGEDIALOG_H
