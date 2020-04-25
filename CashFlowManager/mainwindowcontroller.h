#ifndef MAINWINDOWCONTROLLER_H
#define MAINWINDOWCONTROLLER_H

#include <memory>

class SystemDataSource;

class MainWindowController
{

public:
    MainWindowController();
    ~MainWindowController();

private:
    std::unique_ptr<SystemDataSource> sds;
};

#endif // MAINWINDOWCONTROLLER_H
