#include "../../include/qt/mainwindow.h"
#include "../../include/qt/ui_mainwindow.h"

MainWindow::MainWindow(Blockchain *bcPtrIn, QString fileName, QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    bcPtr = bcPtrIn;
    websiteFile = fileName;
};

MainWindow::~MainWindow()
{
    delete ui;
}



void MainWindow::showMainWindow()
{
    this->show();  // Show the main window
}


void MainWindow::on_btnLogin_clicked()
{
    this->hide();
    Login *login = new Login(bcPtr, this);
    connect(login, &Login::backPressed, this, &MainWindow::showMainWindow);
    login->show();
}


void MainWindow::on_btnRegister_clicked()
{
    this->hide();
    RegisterWindow *registerWindow = new RegisterWindow(this);
    connect(registerWindow, &RegisterWindow::backPressed, this, &MainWindow::showMainWindow);
    registerWindow->show();
}


void MainWindow::on_btnResults_clicked()
{
    this->hide();
    ResultsWindow *resultsWindow = new ResultsWindow(bcPtr, this);
    connect(resultsWindow, &ResultsWindow::backPressed, this, &MainWindow::showMainWindow);
    resultsWindow->show();
}

void MainWindow::on_btnBlockchain_clicked()
{
    this->hide();
    BlockchainWindow *blockchainWindow = new BlockchainWindow(bcPtr, websiteFile, this);
    connect(blockchainWindow, &BlockchainWindow::backPressed, this, &MainWindow::showMainWindow);
    blockchainWindow->show();
}

