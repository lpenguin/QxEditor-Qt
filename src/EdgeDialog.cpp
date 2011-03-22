#include "EdgeDialog.h"
#include "ui_EdgeDialog.h"

EdgeDialog::EdgeDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::EdgeDialog)
{
    ui->setupUi(this);
    connect( ui->buttonBox, SIGNAL(accepted()), this, SLOT(buttonboxAccepted()));
}

EdgeDialog::~EdgeDialog()
{
    delete ui;
}

int EdgeDialog::ShowEdge(BaseEdge *edge)
{
    m_edge = edge;
    ui->edgeWidget->ShowEdge( edge );
    exec();
}
void EdgeDialog::buttonboxAccepted()
{
    ui->edgeWidget->WriteEdge( m_edge );
}

void EdgeDialog::setEdgeWidget(BaseEdgeWidget *widget)
{
    if( ui->edgeWidget ){
        ui->verticalLayout->removeWidget( ui->edgeWidget);
        delete ui->edgeWidget;
    }
    ui->edgeWidget = widget;
    ui->verticalLayout->insertWidget(0,  widget );
}
