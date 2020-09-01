#include "addincometransactiondialogcontroller.h"
#include "incomeinterface.h"
#include "salaryincome.h"
#include "supplementalincome.h"
#include "validator.h"

AddIncomeTransactionDialogController::AddIncomeTransactionDialogController(IncomeInterface& localIncomeInterface)
:
    incomeInterface(localIncomeInterface)
{

}

bool AddIncomeTransactionDialogController::verifyTransactionDescription(QString description) const
{
    return Validator::verifyDescription(description);
}

bool AddIncomeTransactionDialogController::verifyTransactionDate(QDate date) const
{
    return Validator::verifyDate(date);
}

bool AddIncomeTransactionDialogController::verifyTransactionAmount(QString amount) const
{
    return Validator::verifyDoubleAmount(amount, 100000.00, false);
}

bool AddIncomeTransactionDialogController::verifyOTAmount(QString amount) const
{
    return Validator::verifyIntAmount(amount, 100, false);
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
