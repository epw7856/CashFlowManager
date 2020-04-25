#include "mainwindowcontroller.h"
#include "systemdatasource.h"

MainWindowController::MainWindowController()
:
    sds(std::make_unique<SystemDataSource>())
{
    sds->loadSystemConfig("../CashFlowManager/SystemConfiguration.json");
}

MainWindowController::~MainWindowController() = default;
