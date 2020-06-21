#include "addincometransactiondialogcontroller.h"
#include "incomeinterface.h"
#include "salaryincome.h"
#include "supplementalincome.h"

AddIncomeTransactionDialogController::AddIncomeTransactionDialogController(IncomeInterface& localIncomeInterface)
:
    incomeInterface(localIncomeInterface)
{

}

void AddIncomeTransactionDialogController::addSalaryIncomeTransaction(const QDate& date, const double amount, const int overtime)
{
    SalaryIncome transaction(date, amount, overtime);
    incomeInterface.addSalaryPayment(transaction);
}

void AddIncomeTransactionDialogController::addSupplementalIncomeTransaction(const QDate& date, const QString& description, const double amount)
{
    SupplementalIncome transaction(date, amount, description.toStdString());
    incomeInterface.addSupplementalPayment(transaction);
}
