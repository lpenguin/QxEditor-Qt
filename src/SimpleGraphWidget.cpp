#include "SimpleGraphWidget.h"
#include "ui_SimpleGraphWidget.h"

SimpleGraphWidget::SimpleGraphWidget(QWidget *parent) :
    BaseGraphWidget(parent),
    ui(new Ui::SimpleGraphWidget)
{
    ui->setupUi(this);
}

SimpleGraphWidget::~SimpleGraphWidget()
{
    delete ui;
}

void SimpleGraphWidget::ShowGraph(Graph *graph)
{
    SimpleGraphInfo * info;
    if( info = qobject_cast<SimpleGraphInfo *>(graph->info())){
        ui->actionsEdit->setPlainText( info->actions() );
    }
}

void SimpleGraphWidget::WriteGraph(Graph *graph)
{
    SimpleGraphInfo * info;
    if( info = qobject_cast<SimpleGraphInfo *>(graph->info())){
        info->setActions( ui->actionsEdit->toPlainText());
    }
}
