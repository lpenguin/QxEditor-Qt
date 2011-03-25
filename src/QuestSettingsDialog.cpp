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
void QuestSettingsDialog::ShowGraph(Graph * graph){
//    if( qobject_cast<SimpleGraph*>(graph)){
        GraphInfo * info =  graph->info();
        ui->questNameEdit->setText( info->name() );
        ui->questDescriptionEdit->setPlainText( info->description() );

        if( exec() ){
            info->setName( ui->questNameEdit->text() );
            info->setDescription( ui->questDescriptionEdit->toPlainText() );
        }
//    }
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
