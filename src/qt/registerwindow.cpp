#include "../../include/qt/registerwindow.h"
#include "../../include/logic/UserManager.h"
#include "../../include/qt/ui_registerwindow.h"
#include <QRegularExpressionValidator>
#include <QRegularExpression>
#include <QKeyEvent>

RegisterWindow::RegisterWindow(QWidget *parent)
    : QDialog(parent)
    , ui(new Ui::RegisterWindow)
{
    ui->setupUi(this);
    ui->linePassword->setEchoMode(QLineEdit::Password);
    ui->linePassword->setMaxLength(20);

    // Set up the regular expression for alphanumeric input
    QRegularExpression regex("^[A-Za-z0-9]+$");  // Allows only alphanumeric characters
    QRegularExpressionValidator *validator = new QRegularExpressionValidator(regex, this);
    ui->lineUsername->setMaxLength(20);

    // Apply the validator to the username QLineEdit
    ui->lineUsername->setValidator(validator);
    setWindowTitle("Registration Window");
}

RegisterWindow::~RegisterWindow()
{
    delete ui;
}

void RegisterWindow::on_btnBack_clicked()
{
    this->close();
}


void RegisterWindow::on_passwordBox_checkStateChanged(const Qt::CheckState &arg1)
{
    // Toggle the echo mode between Normal (show password) and Password (hide password)
    if (ui->linePassword->echoMode() == QLineEdit::Password) {
        ui->linePassword->setEchoMode(QLineEdit::Normal);  // Show password
    } else {
        ui->linePassword->setEchoMode(QLineEdit::Password);  // Hide password
    }
}


void RegisterWindow::on_btnSubmit_clicked()
{
    std::string username = ui->lineUsername->text().toStdString();
    std::string password = ui->linePassword->text().toStdString();
    if (username == "" || password == ""){
        ui->labelResponse->setText("Enter a valid username/password");
    } else if (UserManager::registerUser(username, password)){
        ui->labelResponse->setText("You are now registered!");
    } else {
        ui->labelResponse->setText("Username is already taken");
    }
}

void RegisterWindow::closeEvent(QCloseEvent *event)
{
    emit backPressed(); // just goes back
}

// Override keyPressEvent to trigger the submit button when Enter is pressed
void RegisterWindow::keyPressEvent(QKeyEvent *event)
{
    if (event->key() == Qt::Key_Return || event->key() == Qt::Key_Enter) {
        // If Enter key is pressed, trigger the submit button
        on_btnSubmit_clicked();
    } else {
        QDialog::keyPressEvent(event);  // handle other key presses
    }
}
