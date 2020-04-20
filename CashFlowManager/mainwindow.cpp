#include "mainwindow.h"
#include "mainwindowcontroller.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow),
    controller(std::make_shared<MainWindowController>())
{
    ui->setupUi(this);
}

MainWindow::~MainWindow()
{
    delete ui;
}
