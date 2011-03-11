#include "QuestSettingsDialog.h"
#include "ui_QuestSettingsDialog.h"

QuestSettingsDialog::QuestSettingsDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::QuestSettingsDialog)
{
    ui->setupUi(this);
}

QuestSettingsDialog::~QuestSettingsDialog()
{
    delete ui;
}
void QuestSettingsDialog::ShowGraph(BaseGraph * graph){
    ui->questNameEdit->setText( graph->name() );
    ui->questDescriptionEdit->setPlainText( graph->description() );

    if( exec() ){
        graph->setName( ui->questNameEdit->text() );
        graph->setDescription( ui->questDescriptionEdit->toPlainText() );
    }
}

void QuestSettingsDialog::changeEvent(QEvent *e)
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
