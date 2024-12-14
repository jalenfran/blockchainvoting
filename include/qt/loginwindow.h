#ifndef LOGINWINDOW_H
#define LOGINWINDOW_H

#include <QDialog>
#include <QCloseEvent>
#include "votingscreen.h"

namespace Ui {
class Login;
}

class Login : public QDialog
{
    Q_OBJECT

public:
    explicit Login(Blockchain *bcPtrIn, QWidget *parent = nullptr);
    ~Login();

signals:
    void backPressed();

protected:
    void closeEvent(QCloseEvent *event) override;
    void keyPressEvent(QKeyEvent *event) override;

private slots:

    void on_btnBack_clicked();

    void on_passwordBox_checkStateChanged(const Qt::CheckState &arg1);

    void on_btnSubmit_clicked();

private:
    Ui::Login *ui;
    Blockchain *bcPtr;
};

#endif // LOGINWINDOW_H
