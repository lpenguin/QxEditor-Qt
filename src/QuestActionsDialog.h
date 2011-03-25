#ifndef QUESTACTIONSDIALOG_H
#define QUESTACTIONSDIALOG_H

#include <QDialog>
#include "BaseGraph.h"
#include "SimpleGraph.h"
#include "BaseWidgets.h"
namespace Ui {
    class QuestActionsDialog;
}
using namespace Graphs;

class GraphDialog : public QDialog {
    Q_OBJECT
public:
    GraphDialog(QWidget *parent = 0);
    ~GraphDialog();
    int ShowGraph(Graph * graph);
    void setGraphWidget( BaseGraphWidget * widget);
protected:
    void changeEvent(QEvent *e);

private:
    Ui::QuestActionsDialog *ui;

    Graph * m_graph;
public slots:
    void buttonBoxTriggered();
};

#endif // QUESTACTIONSDIALOG_H
