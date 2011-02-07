#ifndef QUESTACTIONSDIALOG_H
#define QUESTACTIONSDIALOG_H

#include <QDialog>
#include "Graph.h"

namespace Ui {
    class QuestActionsDialog;
}

class QuestActionsDialog : public QDialog {
    Q_OBJECT
public:
    QuestActionsDialog(QWidget *parent = 0);
    ~QuestActionsDialog();
    void ShowGraph(Graph * graph);
protected:
    void changeEvent(QEvent *e);

private:
    Ui::QuestActionsDialog *ui;

    Graph * m_graph;
};

#endif // QUESTACTIONSDIALOG_H
