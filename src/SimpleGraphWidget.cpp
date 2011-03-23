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

void SimpleGraphWidget::ShowGraph(BaseGraph *graph)
{
}

void SimpleGraphWidget::WriteGraph(BaseGraph *graph)
{
}
