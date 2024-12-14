#include "../../include/qt/votingscreen.h"
#include "../../include/qt/ui_votingscreen.h"
#include <QRegularExpressionValidator>
#include <QRegularExpression>
#include <QKeyEvent>
#include <QThread>

VotingScreen::VotingScreen(Blockchain *bcPtrIn, const QString &usernameIn, QWidget *parent)
    : QDialog(parent)
    , ui(new Ui::VotingScreen)
{
    bcPtr = bcPtrIn;
    username = usernameIn;
    ui->setupUi(this);

    // Set up the regular expression for alphanumeric input
    QRegularExpression regex("^[A-Za-z]+$");  // Allows only alphanumeric characters
    QRegularExpressionValidator *validator = new QRegularExpressionValidator(regex, this);
    ui->lineCandidate->setMaxLength(20);

    // Apply the validator to the username QLineEdit
    ui->lineCandidate->setValidator(validator);
    buttonState = 0;
    setWindowTitle("Voting Screen");
}

VotingScreen::~VotingScreen()
{
    delete ui;
}

void VotingScreen::on_btnVote_clicked()
{
    if (buttonState == 0){
        std::string vote = ui->lineCandidate->text().toStdString();
        if (vote == ""){
            ui->labelStatus->setText("Enter valid candidate");
        } else {
            buttonState = 1;
            ui->labelStatus->setText("Mining block...");
            ui->btnVote->setText("Waiting");
            QCoreApplication::processEvents();

            QThread::msleep(10);  // 10 ms delay
            QCoreApplication::processEvents();//

            VotingCounter::addVote(bcPtr, vote, username.toStdString());
            ui->labelStatus->setText("Vote Counted");
            ui->lineCandidate->setReadOnly(true);
            ui->btnVote->setText("Back");
            buttonState = 2;
        }
    } else if (buttonState == 2){
        emit backPressed();
        this->close();
    }
}

void VotingScreen::closeEvent(QCloseEvent *event)
{
    emit backPressed(); // just goes back
}

// Override keyPressEvent to trigger the submit button when vote/back is pressed
void VotingScreen::keyPressEvent(QKeyEvent *event)
{
    if (event->key() == Qt::Key_Return || event->key() == Qt::Key_Enter && buttonState != 1) {
        // If Enter key is pressed, trigger the submit button
        on_btnVote_clicked();
    } else {
        QDialog::keyPressEvent(event);  // handle other key presses
    }
}
