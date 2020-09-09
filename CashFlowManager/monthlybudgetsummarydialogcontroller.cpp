#include "currencyutilities.h"
#include "dateutilities.h"
#include "expenseinterface.h"
#include "incomeinterface.h"
#include "investmentinterface.h"
#include "mortgageinterface.h"
#include "monthlybudgetsummarydialogcontroller.h"

MonthlyBudgetSummaryDialogController::MonthlyBudgetSummaryDialogController(ExpenseInterface &localExpenseInterface,
                                                                           IncomeInterface &localIncomeInterface,
                                                                           InvestmentInterface &localInvestmentInterface,
                                                                           MortgageInterface &localMortgageInterface)
:
    expenseInterface(localExpenseInterface),
    incomeInterface(localIncomeInterface),
    investmentInterface(localInvestmentInterface),
    mortgageInterface(localMortgageInterface)
{

}

QString MonthlyBudgetSummaryDialogController::getMonthlyCashSaved(int month) const
{
    int currentYear = QDate::currentDate().year();
    std::pair<QDate, QDate> dates = DateUtilities::getMonthlyDates(currentYear, month);

    double amount = (incomeInterface.getMonthlyIncomeTotal(currentYear, month) -
                     expenseInterface.getMonthlyExpenseTotal(currentYear, month) -
                     investmentInterface.getMonthlyInvestmentTotal(currentYear, month) -
                     mortgageInterface.getAdditionalPrincipalPaymentTotalByDate(dates.first, dates.second));

    return QString::fromStdString(CurrencyUtilities::formatCurrency(amount));
}
