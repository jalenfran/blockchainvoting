#ifndef BLOCKCHAINWINDOW_H
#define BLOCKCHAINWINDOW_H

#include <QDialog>
#include "loginwindow.h"
#include <QHBoxLayout>

namespace Ui {
class BlockchainWindow;
}

class BlockchainWindow : public QDialog
{
    Q_OBJECT

public:
    explicit BlockchainWindow(Blockchain *bcPtrIn, QString fileName, QWidget *parent = nullptr);
    ~BlockchainWindow();

signals:
    void backPressed();

protected:
    void closeEvent(QCloseEvent *event) override;
    void keyPressEvent(QKeyEvent *event) override;

private slots:
    void onBackButtonClicked();
    void onGenerateWebsiteButtonClicked();

private:
    Ui::BlockchainWindow *ui;
    Blockchain *bcPtr;
    QString websiteFile;
    QHBoxLayout *blockLayout;
    QPushButton *backButton;
    QPushButton *generateWebsiteButton;

    void setupUi();
    void addBlockWidget(Block block);

};

#endif // BLOCKCHAINWINDOW_H
