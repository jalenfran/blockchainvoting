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
    explicit ResultsWindow(Blockchain *bc, QWidget *parent = nullptr);
    ~ResultsWindow();

    // Method to add a new result (name and integer value)
    void addResult(const QString &name, int value);

signals:
    void backPressed();

private slots:
    void on_btnBack_clicked();

private:
    Ui::ResultsWindow *ui;
};

#endif // RESULTSWINDOW_H
