#include "../../include/qt/mainwindow.h"
#include "../../include/logic/UserManager.h"
#include "../../include/qt/loadingdialog.h"

#include <QApplication>
#include <QLocale>
#include <QTranslator>
#include <QDir>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    QTranslator translator;
    const QStringList uiLanguages = QLocale::system().uiLanguages();
    for (const QString &locale : uiLanguages) {
        const QString baseName = "votingGUI_" + QLocale(locale).name();
        if (translator.load(":/i18n/" + baseName)) {
            a.installTranslator(&translator);
            break;
        }
    }

    QString appDir = QCoreApplication::applicationDirPath();

    QDir dir(appDir);

    // Loop to navigate up the directory hierarchy until we find the 'data' folder
    while (!dir.exists("data")) {
        if (!dir.cdUp()) {
            // If we can't navigate up any further (i.e., we've reached the root), stop searching
            qDebug() << "Reached the root directory without finding 'data' folder.";
        }
    }

    // Now that we're at the correct directory, construct the path to 'data/users.txt'
    QString dataFilePath = dir.filePath("data/users.txt");
    QString websiteFilePath = dir.filePath("website/index.html");

    // displays loading display
    LoadingDialog *loadingDialog = new LoadingDialog();
    loadingDialog->show();

    a.processEvents(); // ensures dialog shows

    // loads database
    UserManager::loadUserDatabase(dataFilePath.toStdString());
    Blockchain bc;
    createBlockchain(&bc);

    loadingDialog->accept();

    MainWindow w(&bc, websiteFilePath);
    
    w.show();
    return a.exec();
}
