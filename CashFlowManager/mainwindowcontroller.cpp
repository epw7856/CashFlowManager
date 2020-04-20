#include "mainwindowcontroller.h"
#include "systemdatasource.h"

MainWindowController::MainWindowController()
:
    sds(std::make_shared<SystemDataSource>())
{
    sds->loadSystemConfig("../CashFlowManager/SystemConfiguration.json");
}
