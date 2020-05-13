#ifndef MAINWINDOWCONTROLLER_H
#define MAINWINDOWCONTROLLER_H

#include <memory>
#include <QObject>
#include <string>
#include <vector>

class MonthlyBudgetSummaryDialog;
class YearlyBudgetSummaryDialog;
class QDate;
class SystemDataSource;

class MainWindowController : public QObject
{
    Q_OBJECT
public:
    MainWindowController(SystemDataSource& sds);
    ~MainWindowController();

    // Supporting functions for Main Window information display
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

    // Supporting functions for Main Window auxilary actions
    void showYearlyBudgetSummaryDialog(QWidget* parent);
    void showMonthlyBudgetSummaryDialog(QWidget* parent);

private:
    SystemDataSource& sds;

    std::unique_ptr<YearlyBudgetSummaryDialog> yearlyBudgetDialog;
    std::unique_ptr<MonthlyBudgetSummaryDialog> monthlyBudgetDialog;
};

#endif // MAINWINDOWCONTROLLER_H
