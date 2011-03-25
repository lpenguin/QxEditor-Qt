#include "SimpleVerWidget.h"
#include "ui_SimpleVerWidget.h"

SimpleVerWidget::SimpleVerWidget(QWidget *parent) :
    BaseVerWidget(parent),
    ui(new Ui::SimpleVerWidget)
{
    ui->setupUi(this);
}

SimpleVerWidget::~SimpleVerWidget()
{
    delete ui;
}

void SimpleVerWidget::ShowVer(Ver *ver)
{
    SimpleVerInfo * info;
    if( info = qobject_cast<SimpleVerInfo *>(ver->info())){
        ui->actionsEdit->setText( info->actions());
        ui->verIdEdit->setText( info->id() );
        ui->textEdit->setText(info->text() );
        type2radio( info->verType());
    }
}

void SimpleVerWidget::WriteVer(Ver *ver)
{
    SimpleVerInfo * info;
    if( info = qobject_cast<SimpleVerInfo *>(ver->info())){
        info->setActions( ui->actionsEdit->toPlainText() );
        info->setId( ui->verIdEdit->text() );
        info->setText( ui->textEdit->toPlainText() );
        info->setVerType( radio2type() );
    }
}

VerInfo::VerType SimpleVerWidget::radio2type ( void ){
    if( ui->odinaryRadio->isChecked())
        return VerInfo::odinary;
    if( ui->startRadio->isChecked())
        return VerInfo::start;
    if( ui->winRadio->isChecked())
        return VerInfo::win;
    if( ui->failRadio->isChecked())
        return VerInfo::fail;
    return VerInfo::odinary;
}

void SimpleVerWidget::type2radio( VerInfo::VerType type){
    switch( type ){
    case VerInfo::odinary:
        ui->odinaryRadio->setChecked(true);
        break;
    case VerInfo::start:
        ui->startRadio->setChecked(true);
        break;
    case VerInfo::win:
        ui->winRadio->setChecked(true);
        break;
    case VerInfo::fail:
        ui->failRadio->setChecked(true);
        break;

    }
}
