#ifndef QUESTACTIONSDIALOG_H
#define QUESTACTIONSDIALOG_H

#include <QDialog>
#include "BaseGraph.h"

namespace Ui {
    class QuestActionsDialog;
}

class QuestActionsDialog : public QDialog {
    Q_OBJECT
public:
    QuestActionsDialog(QWidget *parent = 0);
    ~QuestActionsDialog();
    void ShowGraph(BaseGraph * graph);
protected:
    void changeEvent(QEvent *e);

private:
    Ui::QuestActionsDialog *ui;

    BaseGraph * m_graph;
};

#endif // QUESTACTIONSDIALOG_H
