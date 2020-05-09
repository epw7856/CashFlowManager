#ifndef MAINWINDOWCONTROLLER_H
#define MAINWINDOWCONTROLLER_H

#include <string>
#include <vector>

class QDate;
class SystemDataSource;

class MainWindowController
{
public:
    MainWindowController(SystemDataSource& sds);

    // Supporting functions for MainWindow information display
    std::pair<QDate, QDate> getCurrentMonthDates() const;
    std::string getCurrentMonthAndYear() const;
    std::string getBudgetStatusStatement() const;
    double getMonthlyExpenseTotal() const;
    double getMonthlyBudgetTotal() const;
    double getMonthlyInvestmentTotal() const;
    double getMonthlyIncomeTotal() const;
    double getMonthlyCashSavedTotal() const;
    double getMonthlyBudgetSurplus() const;
    double getYearlyExpenseTotal() const;
    double getYearlyIncomeTotal() const;
    double getYearlyInvestmentTotal() const;
    double getYearlyCashSavedTotal() const;
    double getYearlyAmountSaved() const;
    double getYearlySavingsRatio() const;
    double getMonthlyRemainingBudget() const;
    std::vector<std::pair<std::string, double>> getInvestmentTypesAndYearlyTotals() const;

private:
    SystemDataSource& sds;
};

#endif // MAINWINDOWCONTROLLER_H
