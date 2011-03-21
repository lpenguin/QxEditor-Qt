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
    if( qobject_cast<SimpleGraph*>( graph) ){
        SimpleGraphInfo * info = (SimpleGraphInfo *)(graph->info());
        ui->actionsEdit->setPlainText( info->actions() );
        if( exec() ){
            info->setActions( ui->actionsEdit->toPlainText() );
        }
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
