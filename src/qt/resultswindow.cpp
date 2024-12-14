#include "../../include/qt/resultswindow.h"
#include "../../include/qt/ui_resultswindow.h"
#include <QVBoxLayout>
#include <QLabel>
#include <QScrollArea>
#include <QDialog>
#include <QGroupBox>
#include <QWidget>
#include <string>
#include <vector>

ResultsWindow::ResultsWindow(Blockchain *bcPtr, QWidget *parent)
    : QDialog(parent), ui(new Ui::ResultsWindow)
{
    ui->setupUi(this);

    std::vector<std::pair<std::string, int>> results = VotingCounter::tallyAndSortVotes(bcPtr);

    // Create a QVBoxLayout to arrange the group boxes vertically
    QVBoxLayout *layout = new QVBoxLayout();

    for (const auto& pair : results) {
        // Create a QGroupBox for each pair
        QGroupBox *groupBox = new QGroupBox(this);

        // Create a QHBoxLayout for the contents of the group box
        QHBoxLayout *hLayout = new QHBoxLayout();

        // Create the label with the name and number
        QString labelText = QString("%1: %2").arg(QString::fromStdString(pair.first)).arg(QString::number(pair.second));
        QLabel *label = new QLabel(labelText, this);

        // Add the label to the layout
        hLayout->addWidget(label);

        // Set the layout to the group box
        groupBox->setLayout(hLayout);

        groupBox->setMaximumHeight(50);

        // Add the group box to the main layout
        layout->addWidget(groupBox);
    }

    // Create a QWidget to hold the layout
    QWidget *containerWidget = new QWidget(this);
    containerWidget->setLayout(layout);

    // Create a QScrollArea to allow scrolling if the content exceeds the window size
    QScrollArea *scrollArea = new QScrollArea(this);
    scrollArea->setWidgetResizable(true);  // Make sure the content adjusts to the area size
    scrollArea->setWidget(containerWidget);
    scrollArea->setMaximumHeight(200);

    // Set the scroll area as the main layout widget
    QVBoxLayout *mainLayout = new QVBoxLayout(this);
    mainLayout->addWidget(scrollArea);

    setLayout(mainLayout);
    setWindowTitle("Results Viewer");

}

ResultsWindow::~ResultsWindow()
{
    delete ui;
}

void ResultsWindow::on_btnBack_clicked()
{
    this->close();
}

void ResultsWindow::closeEvent(QCloseEvent *event)
{
    emit backPressed(); // just goes back
}
