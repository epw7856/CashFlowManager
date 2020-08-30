#include "cashflowmanagerapplication.h"
#include "mainwindow.h"
#include <QApplication>
#include <QDesktopWidget>
#include <QMessageBox>

int main(int argc, char *argv[])
{
    CashFlowManagerApplication a(argc, argv);
    MainWindow w;
    w.show();
    return a.exec();
}
