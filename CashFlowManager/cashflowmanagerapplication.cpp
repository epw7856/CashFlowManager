#include "cashflowmanagerapplication.h"
#include <QMessageBox>

CashFlowManagerApplication::CashFlowManagerApplication(int& argc, char** argv)
:
    QApplication(argc, argv)
{

}

bool CashFlowManagerApplication::notify(QObject *receiver, QEvent *event)
{
    try
    {
        return QApplication::notify(receiver, event);
    }
    catch(std::exception& ex)
    {
        QMessageBox::critical(nullptr, "Error", "Exception: " + QString::fromStdString(ex.what()), QMessageBox::Ok);
    }
    return false;
}
