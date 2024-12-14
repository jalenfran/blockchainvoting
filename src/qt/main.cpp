#include "../../include/qt/mainwindow.h"
#include "../../include/logic/UserManager.h"
#include "../../include/qt/loadingdialog.h"

#include <QApplication>
#include <QLocale>
#include <QTranslator>

void termination(Blockchain *bc);

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

    // displays loading display
    LoadingDialog *loadingDialog = new LoadingDialog();
    loadingDialog->show();

    a.processEvents(); // ensures dialog shows

    // loads database
    UserManager::loadUserDatabase();
    Blockchain bc;
    createBlockchain(&bc);

    loadingDialog->accept();

    MainWindow w(&bc);

    QObject::connect(&w, &QWidget::destroyed, &a, &QApplication::quit);
    
    w.show();
    return a.exec();
}

void termination(Blockchain *bc){
    writeToWebsite(bc);
    QApplication::quit();
}
