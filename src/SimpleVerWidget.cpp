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

void SimpleVerWidget::ShowVer(BaseVer *ver)
{
    SimpleVerInfo * info;
    if( info = qobject_cast<SimpleVerInfo *>(ver->info())){
        ui->actionsEdit->setText( info->actions());
        ui->verIdEdit->setText( info->id() );
        ui->textEdit->setText(info->text() );
        type2radio( info->verType());
    }
}

void SimpleVerWidget::WriteVer(BaseVer *ver)
{
    SimpleVerInfo * info;
    if( info = qobject_cast<SimpleVerInfo *>(ver->info())){
        info->setActions( ui->actionsEdit->toPlainText() );
        info->setId( ui->verIdEdit->text() );
        info->setText( ui->textEdit->toPlainText() );
        info->setVerType( radio2type() );
    }
}

BaseVerInfo::VerType SimpleVerWidget::radio2type ( void ){
    if( ui->odinaryRadio->isChecked())
        return BaseVerInfo::odinary;
    if( ui->startRadio->isChecked())
        return BaseVerInfo::start;
    if( ui->winRadio->isChecked())
        return BaseVerInfo::win;
    if( ui->failRadio->isChecked())
        return BaseVerInfo::fail;
    return BaseVerInfo::odinary;
}

void SimpleVerWidget::type2radio( BaseVerInfo::VerType type){
    switch( type ){
    case BaseVerInfo::odinary:
        ui->odinaryRadio->setChecked(true);
        break;
    case BaseVerInfo::start:
        ui->startRadio->setChecked(true);
        break;
    case BaseVerInfo::win:
        ui->winRadio->setChecked(true);
        break;
    case BaseVerInfo::fail:
        ui->failRadio->setChecked(true);
        break;

    }
}
