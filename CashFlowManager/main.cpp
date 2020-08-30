#include "mainwindow.h"
#include <QApplication>
#include <QDesktopWidget>
#include <QMessageBox>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    try
    {
        MainWindow w;
        w.show();
    }
    catch (const std::exception& ex)
    {
        QMessageBox::critical(nullptr, "Error", "Exception: " + QString::fromStdString(ex.what()), QMessageBox::Ok);
        exit(1);
    }

    return a.exec();
}
