#ifndef QUESTSETTINGSDIALOG_H
#define QUESTSETTINGSDIALOG_H

#include <QDialog>
#include "BaseGraph.h"
#include "SimpleGraph.h"
#include <QFileDialog>
namespace Ui {
    class QuestSettingsDialog;
}
using namespace Graphs;
class QuestSettingsDialog : public QDialog {
    Q_OBJECT
public:
    QuestSettingsDialog(QWidget *parent = 0, const QString & playerPath = QString());
    ~QuestSettingsDialog();
    void ShowGraph(Graph * graph);
    void setPlayerPath( const QString & playerPath ){
        m_playerPath = playerPath;
    }

protected:
    void changeEvent(QEvent *e);

private:
    Ui::QuestSettingsDialog *ui;
    QString m_playerPath;
public slots:
    void on_addButton_clicked();
    void on_browseButton_clicked();
    void on_editButton_clicked();
    void on_deleteButton_clicked();
    void on_libsList_itemClicked();
};

#endif // QUESTSETTINGSDIALOG_H
