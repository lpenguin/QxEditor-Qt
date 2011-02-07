#ifndef QUESTSETTINGSDIALOG_H
#define QUESTSETTINGSDIALOG_H

#include <QDialog>
#include "Graph.h"

namespace Ui {
    class QuestSettingsDialog;
}

class QuestSettingsDialog : public QDialog {
    Q_OBJECT
public:
    QuestSettingsDialog(QWidget *parent = 0);
    ~QuestSettingsDialog();
    void ShowGraph(Graph * graph);
protected:
    void changeEvent(QEvent *e);

private:
    Ui::QuestSettingsDialog *ui;
};

#endif // QUESTSETTINGSDIALOG_H
