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
     //ui->declarativeView->setSource( QUrl::fromLocalFile(playerPath));
     //QObject * o = (QObject*)ui->declarativeView->rootObject();
     //o->setProperty("questPath", path);
    QString indexPath = QString("%1%2index.html").arg(playerPath).arg(QDir::separator());
    QString questInfoPath = QString("%1%2quest.info").arg(playerPath).arg(QDir::separator());

    QFile file(questInfoPath);
    if (!file.open(QIODevice::WriteOnly | QIODevice::Text))
             return;

    QTextStream out(&file);
    out << QString("{ \"path\" : \"%1\" }").arg(QUrl::fromLocalFile(path).toString());
    file.close();


    ui->webView->load(QUrl::fromLocalFile(indexPath));
    //ui->webView->load(QUrl("http://qt.nokia.com/"));
    qDebug()<<QUrl::fromLocalFile(indexPath).toString();
    ui->webView->show();
     //ui->declarativeView->rootContext()
     //ui->declarativeView->show();
    exec();
}
