#include "SimpleEdgeWidget.h"
#include "ui_SimpleEdgeWidget.h"

SimpleEdgeWidget::SimpleEdgeWidget(QWidget *parent) :
    BaseEdgeWidget(parent),
    ui(new Ui::SimpleEdgeWidget)
{
    ui->setupUi(this);
}

SimpleEdgeWidget::~SimpleEdgeWidget()
{
    delete ui;
}

void SimpleEdgeWidget::ShowEdge(BaseEdge *edge)
{
    SimpleEdgeInfo * info;
    if( info = qobject_cast<SimpleEdgeInfo *>(edge->info())){
        ui->actionsEdit->setText( info->actions());
        ui->conditionsEdit->setPlainText( info->conditions());
        ui->textEdit->setText( info->text());
        ui->questionEdit->setText( info->question());

        ui->edgeIdEdit->setText(info->id());
    }
}

void SimpleEdgeWidget::WriteEdge(BaseEdge *edge)
{
    SimpleEdgeInfo * info;
    if( info = qobject_cast<SimpleEdgeInfo *>(edge->info())){
        info->setActions( ui->actionsEdit->toPlainText() );
        info->setConditions( ui->conditionsEdit->toPlainText() );
        info->setId( ui->edgeIdEdit->text() );
        info->setText( ui->textEdit->toPlainText() );
        info->setQuestion( ui->questionEdit->toPlainText() );
    }
}
