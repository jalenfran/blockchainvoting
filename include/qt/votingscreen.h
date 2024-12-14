#ifndef VOTINGSCREEN_H
#define VOTINGSCREEN_H

#include <QDialog>
#include "../logic/VotingCounter.h"

namespace Ui {
class VotingScreen;
}

class VotingScreen : public QDialog
{
    Q_OBJECT

public:
    explicit VotingScreen(Blockchain *bcPtrIn, const QString &username, QWidget *parent = nullptr);
    ~VotingScreen();

signals:
    void backPressed();

protected:
    void closeEvent(QCloseEvent *event) override;
    void keyPressEvent(QKeyEvent *event) override;

private slots:
    void on_btnVote_clicked();

private:
    Ui::VotingScreen *ui;
    QString username;
    Blockchain *bcPtr;
    // 0 correlates with vote, 1  -waiting, 2 - back
    int buttonState;
};

#endif // VOTINGSCREEN_H
