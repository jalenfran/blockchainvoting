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
    explicit VotingScreen(Blockchain *bc, const QString &username, QWidget *parent = nullptr);
    ~VotingScreen();

signals:
    void backPressed();

private slots:
    void on_btnVote_clicked();

private:
    Ui::VotingScreen *ui;
    QString username;
    Blockchain *bc;
    bool isVoteButton;
};

#endif // VOTINGSCREEN_H
