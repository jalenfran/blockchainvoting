#include "../../include/qt/blockchainwindow.h"
#include "../../include/qt/ui_blockchainwindow.h"
#include <QScrollArea>
#include <QLabel>
#include <QFrame>
#include <QPushButton>
#include <QKeyEvent>
#include "../../include/logic/hashing.h"

BlockchainWindow::BlockchainWindow(Blockchain *bcPtrIn, QString fileName, QWidget *parent)
    : QDialog(parent)
    , ui(new Ui::BlockchainWindow)
{
    ui->setupUi(this);
    bcPtr = bcPtrIn;
    websiteFile = fileName;
    setupUi();
}

BlockchainWindow::~BlockchainWindow()
{
    delete ui;
}

void BlockchainWindow::setupUi()
{
    QScrollArea *scrollArea = new QScrollArea(this);
    QWidget *containerWidget = new QWidget(this);
    blockLayout = new QHBoxLayout(containerWidget);  // Initialize blockLayout

    // Set spacing between blocks
    blockLayout->setSpacing(20);

    for (int i = 0; i < bcPtr->length; i++) {
        addBlockWidget(bcPtr->blocks[i]);
    }

    containerWidget->setLayout(blockLayout);  // Set the layout to blockLayout
    scrollArea->setWidget(containerWidget);
    scrollArea->setWidgetResizable(true);
    scrollArea->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOn);

    QVBoxLayout *mainLayout = new QVBoxLayout(this);
    mainLayout->addWidget(scrollArea);

    // Create buttons
    backButton = new QPushButton(tr("Back"), this);
    generateWebsiteButton = new QPushButton(tr("Generate Website"), this);

    // Connect buttons to slots
    connect(backButton, &QPushButton::clicked, this, &BlockchainWindow::onBackButtonClicked);
    connect(generateWebsiteButton, &QPushButton::clicked, this, &BlockchainWindow::onGenerateWebsiteButtonClicked);

    // Create a horizontal layout for buttons
    QHBoxLayout *buttonLayout = new QHBoxLayout;
    buttonLayout->addWidget(backButton);
    buttonLayout->addWidget(generateWebsiteButton);

    // Add the button layout to the main layout
    mainLayout->addLayout(buttonLayout);

    setLayout(mainLayout);
    setWindowTitle("Blockchain Viewer");
    resize(800, 500);
}

void BlockchainWindow::addBlockWidget(Block block)
{
    QFrame *blockFrame = new QFrame(this);
    blockFrame->setFrameShape(QFrame::Box);
    blockFrame->setLineWidth(2);

    // Set stylesheet for blockFrame
    blockFrame->setStyleSheet("QFrame {"
                              "border: 1px solid gray;"
                              "border-radius: 10px;"
                              "padding: 5px;"
                              "}");

    QVBoxLayout *layout = new QVBoxLayout(blockFrame);
    layout->setContentsMargins(15, 15, 15, 15); // Add padding inside the block
    layout->setSpacing(10); // Set spacing between labels


    QLabel *indexLabel = new QLabel(tr("Block: %1").arg(block.index), blockFrame);
    QLabel *nonceLabel = new QLabel(tr("Nonce: %1").arg(block.nonce), blockFrame);
    QLabel *timestampLabel = new QLabel(tr("Timestamp: %1").arg(block.timestamp), blockFrame);
    QLabel *usernameLabel = new QLabel(tr("Username: %1").arg(block.username), blockFrame);
    QLabel *dataLabel = new QLabel(tr("Data: %1").arg(block.data), blockFrame);

    char hashString[HASH_STRING_LENGTH];
    makeHashString(block.previousHash, hashString);
    QLabel *previousHashLabel = new QLabel(tr("Previous Hash: %1").arg(hashString), blockFrame);

    makeHashString(block.hash, hashString);
    QLabel *hashLabel = new QLabel(tr("Hash: %1").arg(hashString), blockFrame);

    // Set custom styles for labels
    QString labelStyle = "QLabel { font: 12pt 'Arial'; }";
    indexLabel->setStyleSheet(labelStyle);
    nonceLabel->setStyleSheet(labelStyle);
    timestampLabel->setStyleSheet(labelStyle);
    usernameLabel->setStyleSheet(labelStyle);
    dataLabel->setStyleSheet(labelStyle);
    previousHashLabel->setStyleSheet(labelStyle);
    hashLabel->setStyleSheet(labelStyle);

    layout->addWidget(indexLabel);
    layout->addWidget(nonceLabel);
    layout->addWidget(timestampLabel);
    layout->addWidget(usernameLabel);
    layout->addWidget(dataLabel);
    layout->addWidget(previousHashLabel);
    layout->addWidget(hashLabel);

    blockFrame->setLayout(layout);
    blockLayout->addWidget(blockFrame);
    blockFrame->setMaximumWidth(600);
}

void BlockchainWindow::onBackButtonClicked()
{
    this->close();
}

void BlockchainWindow::onGenerateWebsiteButtonClicked()
{
    generateWebsiteButton->setText("Working");
    writeToWebsite(bcPtr, websiteFile.toStdString());
    generateWebsiteButton->setText("Done");
}

void BlockchainWindow::closeEvent(QCloseEvent *event)
{
    emit backPressed();
}

// Override keyPressEvent to trigger the submit button when Enter is pressed
void BlockchainWindow::keyPressEvent(QKeyEvent *event)
{
    if (event->key() == Qt::Key_Return || event->key() == Qt::Key_Enter) {
        // If Enter key is pressed, trigger the generate website button
        onGenerateWebsiteButtonClicked();
    } else {
        QDialog::keyPressEvent(event);  // handle other key presses
    }
}


