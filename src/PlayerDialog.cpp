#include "PlayerDialog.h"
#include "ui_PlayerDialog.h"

PlayerDialog::PlayerDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::PlayerDialog)
{
    ui->setupUi(this);

}

PlayerDialog::~PlayerDialog()
{
    delete ui;
}

void PlayerDialog::Play(const QString &path, const QString & playerPath)
{
//     ui->declarativeView->rootContext()->setContextProperty( "networkManager", &manager );
     ui->declarativeView->setSource( QUrl::fromLocalFile(playerPath));
     QObject * o = (QObject*)ui->declarativeView->rootObject();
     o->setProperty("questPath", path);

     //ui->declarativeView->rootContext()
     ui->declarativeView->show();
     exec();
}
