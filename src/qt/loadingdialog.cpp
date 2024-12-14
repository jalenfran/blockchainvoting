#include "../../include/qt/loadingdialog.h"
#include "../../include/qt/ui_loadingdialog.h"

LoadingDialog::LoadingDialog(QWidget *parent)
    : QDialog(parent)
    , ui(new Ui::LoadingDialog)
{
    ui->setupUi(this);
    setWindowTitle("Loading Screen");
}

LoadingDialog::~LoadingDialog()
{
    delete ui;
}
