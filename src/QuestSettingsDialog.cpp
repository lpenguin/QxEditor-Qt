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

        ui->libsList->clear();
        foreach(QString lib, graph->info()->libraries() ){
            if( !lib.isEmpty() )
                new QListWidgetItem( lib, ui->libsList );
        }

        if( exec() ){
            info->setName( ui->questNameEdit->text() );
            info->setDescription( ui->questDescriptionEdit->toPlainText() );
            QStringList libs;
            for( int i = 0; i < ui->libsList->count(); i++ ){
                QListWidgetItem *item = ui->libsList->item( i );
                if( !item->text().isEmpty() )
                    libs << item->text();
            }

            info->setLibraries( libs );
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
void QuestSettingsDialog::on_addButton_clicked(){
    if( ui->pathEdit->text().isEmpty() )
            return;
    new QListWidgetItem( ui->pathEdit->text(), ui->libsList );
}

void QuestSettingsDialog::on_browseButton_clicked(){

}

void QuestSettingsDialog::on_editButton_clicked(){
    if( ui->pathEdit->text().isEmpty() )
            return;
     QListWidgetItem *item = ui->libsList->currentItem();
     if( item )
        item->setText( ui->pathEdit->text() );
}

void QuestSettingsDialog::on_deleteButton_clicked(){
    qint32 i = ui->libsList->currentRow();
    if( i != -1 )
       delete ui->libsList->takeItem( i );
}

void QuestSettingsDialog::on_libsList_itemClicked(){
    QListWidgetItem *item = ui->libsList->currentItem();
    if( item )
       ui->pathEdit->setText( item->text() );
}
