#ifndef RESULTSWINDOW_H
#define RESULTSWINDOW_H

#include <QDialog>
#include <QVector>
#include <QPair>
#include <QString>
#include "loginwindow.h"

namespace Ui {
class ResultsWindow;
}

class ResultsWindow : public QDialog
{
    Q_OBJECT

public:
    explicit ResultsWindow(Blockchain *bcPtr, QWidget *parent = nullptr);
    ~ResultsWindow();

signals:
    void backPressed();

protected:
    void closeEvent(QCloseEvent *event) override;

private slots:
    void on_btnBack_clicked();

private:
    Ui::ResultsWindow *ui;
};

#endif // RESULTSWINDOW_H
