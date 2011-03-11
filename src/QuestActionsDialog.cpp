#include "QuestActionsDialog.h"
#include "ui_QuestActionsDialog.h"

QuestActionsDialog::QuestActionsDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::QuestActionsDialog)
{
    ui->setupUi(this);
}

QuestActionsDialog::~QuestActionsDialog()
{
    delete ui;
}
void QuestActionsDialog::ShowGraph(BaseGraph * graph){
    ui->actionsEdit->setPlainText( graph->script() );
    if( exec() ){
        graph->setScript( ui->actionsEdit->toPlainText() );
    }
}

void QuestActionsDialog::changeEvent(QEvent *e)
{
    QDialog::changeEvent(e);
    switch (e->type()) {
    case QEvent::LanguageChange:
        ui->retranslateUi(this);
        break;
    default:
        break;
    }
}
