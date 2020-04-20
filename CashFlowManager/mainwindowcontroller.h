#ifndef MAINWINDOWCONTROLLER_H
#define MAINWINDOWCONTROLLER_H

#include <memory>

class SystemDataSource;

class MainWindowController
{

public:
    MainWindowController();

private:
    std::shared_ptr<SystemDataSource> sds = nullptr;
};

#endif // MAINWINDOWCONTROLLER_H
