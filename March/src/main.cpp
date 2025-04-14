#include <QApplication>

#include "MainWindow.h"
#include "Logger.h"

int main(int argc, char* argv[])
{
    MLog::Logger::Init();

    QApplication a(argc, argv);
    a.setWindowIcon(QIcon("://svg/logo.svg"));

    MainWindow w;
    w.show();

    return a.exec();
}