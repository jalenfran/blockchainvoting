#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "loginwindow.h"
#include "registerwindow.h"
#include "resultswindow.h"

QT_BEGIN_NAMESPACE
namespace Ui {
class MainWindow;
}
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(Blockchain *bcIn, QWidget *parent = nullptr);
    ~MainWindow();

private slots:
    void showMainWindow();

    void on_btnLogin_clicked();

    void on_btnRegister_clicked();

    void on_btnResults_clicked();

    void on_btnBlockchain_clicked();

private:
    Ui::MainWindow *ui;
    Blockchain *bc;
};
#endif // MAINWINDOW_H
