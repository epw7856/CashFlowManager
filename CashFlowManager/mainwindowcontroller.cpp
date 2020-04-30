#include "mainwindowcontroller.h"
#include "systemdatasource.h"

MainWindowController::MainWindowController()
:
    sds(std::make_unique<SystemDataSource>("../SystemConfiguration.json"))
{
    sds->loadSystemConfig();

}

MainWindowController::~MainWindowController()
{
    sds->saveSystemConfig();
};
