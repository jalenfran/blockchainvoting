#include "../../include/qt/votingscreen.h"
#include "../../include/qt/ui_votingscreen.h"
#include <QRegularExpressionValidator>
#include <QRegularExpression>
#include <QTimer>

VotingScreen::VotingScreen(Blockchain *bcIn, const QString &usernameIn, QWidget *parent)
    : QDialog(parent)
    , ui(new Ui::VotingScreen)
{
    bc = bcIn;
    username = usernameIn;
    ui->setupUi(this);

    // Set up the regular expression for alphanumeric input
    QRegularExpression regex("^[A-Za-z]+$");  // Allows only alphanumeric characters
    QRegularExpressionValidator *validator = new QRegularExpressionValidator(regex, this);
    ui->lineCandidate->setMaxLength(20);

    // Apply the validator to the username QLineEdit
    ui->lineCandidate->setValidator(validator);
    isVoteButton = true;
}

VotingScreen::~VotingScreen()
{
    delete ui;
}

void VotingScreen::on_btnVote_clicked()
{
    if (isVoteButton){
        ui->labelStatus->setText("Working on block...");
        ui->btnVote->setText("Waiting");
        QCoreApplication::processEvents(); // forces application to update

        // Use a QTimer to ensure the app updates
        QTimer::singleShot(0, this, [this]() {
            VotingCounter::addVote(bc, ui->lineCandidate->text().toStdString(), username.toStdString());
            ui->labelStatus->setText("Vote Counted");
            ui->btnVote->setText("Back");
            isVoteButton = false;
        });
    } else {
        emit backPressed();
        this->close();
    }
}
