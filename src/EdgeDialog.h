#ifndef EDGEDIALOG_H
#define EDGEDIALOG_H

#include <QDialog>
#include "BaseGraph.h"

namespace Ui {
    class EdgeDialog;
}

class EdgeDialog : public QDialog
{
    Q_OBJECT

public:
    explicit EdgeDialog(QWidget *parent = 0);
    ~EdgeDialog();
    int ShowEdge(BaseEdge * edge);
private:
    Ui::EdgeDialog *ui;
    BaseEdge * m_edge;
public slots:
    void buttonboxAccepted();
};

#endif // EDGEDIALOG_H
