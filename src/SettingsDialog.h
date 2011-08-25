#ifndef SETTINGSDIALOG_H
#define SETTINGSDIALOG_H

#include <QDialog>
#include <QFileDialog>

namespace Ui {
    class SettingsDialog;
}

class SettingsDialog : public QDialog
{
    Q_OBJECT

public:
    explicit SettingsDialog(QWidget *parent = 0);
    ~SettingsDialog();
    void setPlayerPath(const QString & playerPath){
        m_playerPath = playerPath;
    }

    QString playerPath() const{
        return m_playerPath;
    }
    int showSettings();

private:
    Ui::SettingsDialog *ui;
    QString m_playerPath;
public slots:
    void browseButtonClicked();
    void accept();
};

#endif // SETTINGSDIALOG_H
