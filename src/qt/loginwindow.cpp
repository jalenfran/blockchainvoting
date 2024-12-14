#include "../../include/qt/loginwindow.h"
#include "../../include/logic/UserManager.h"
#include "../../include/qt/ui_loginwindow.h"
#include <QRegularExpressionValidator>
#include <QRegularExpression>

Login::Login(Blockchain *bcIn, QWidget *parent)
    : QDialog(parent)
    , ui(new Ui::Login)
{

    ui->setupUi(this);
    bc = bcIn;
    ui->linePassword->setEchoMode(QLineEdit::Password);
    ui->linePassword->setMaxLength(20);

    // Set up the regular expression for alphanumeric input
    QRegularExpression regex("^[A-Za-z0-9]+$");  // Allows only alphanumeric characters
    QRegularExpressionValidator *validator = new QRegularExpressionValidator(regex, this);
    ui->lineUsername->setMaxLength(20);

    // Apply the validator to the username QLineEdit
    ui->lineUsername->setValidator(validator);
}

Login::~Login()
{
    delete ui;
}


void Login::on_btnBack_clicked()
{
    emit backPressed();
    this->close();
}


void Login::on_passwordBox_checkStateChanged(const Qt::CheckState &arg1)
{
    // Toggle the echo mode between Normal (show password) and Password (hide password)
    if (ui->linePassword->echoMode() == QLineEdit::Password) {
        ui->linePassword->setEchoMode(QLineEdit::Normal);  // Show password
    } else {
        ui->linePassword->setEchoMode(QLineEdit::Password);  // Hide password
    }
}


void Login::on_btnSubmit_clicked()
{
    if (UserManager::authenticateUser(ui->lineUsername->text().toStdString(), ui->linePassword->text().toStdString())){
        if (!VotingCounter::checkIfVoted(ui->lineUsername->text().toStdString())){
            this->hide();
            VotingScreen *votingScreen = new VotingScreen(bc, ui->lineUsername->text(), this);
            // once the back button is pressed on voting screen we go back to main menu
            connect(votingScreen, &VotingScreen::backPressed, this, &Login::on_btnBack_clicked);
            votingScreen->show();
        } else {
            ui->labelResponse->setText("Already voted");
        }

    } else {
        ui->labelResponse->setText("Authentication failed");
    }
    
}

