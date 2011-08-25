#include "SettingsDialog.h"
#include "ui_SettingsDialog.h"

SettingsDialog::SettingsDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::SettingsDialog)
{
    ui->setupUi(this);
}

SettingsDialog::~SettingsDialog()
{
    delete ui;
}

void SettingsDialog::browseButtonClicked()
{
    QString res  = QFileDialog::getExistingDirectory(this, "Player path", QCoreApplication::applicationDirPath());

    res = QDir::toNativeSeparators(res);
    if( ! res.isEmpty() ){
        ui->playerPath->setText( res );
        m_playerPath = res;
    }
}

int SettingsDialog::showSettings()
{
    ui->playerPath->setText( m_playerPath );
    return QDialog::exec();
}

void SettingsDialog::accept()
{
    m_playerPath = ui->playerPath->text();
    QDialog::accept();
}
