#ifndef MAINWINDOWCONTROLLER_H
#define MAINWINDOWCONTROLLER_H

#include <memory>
#include <QObject>
#include <string>
#include <vector>

class AddExpenseTransactionDialog;
class AssetSummaryDialog;
class AutomaticMonthlyPaymentSummaryDialog;
class ExpenseTypeSummaryDialog;
class MonthlyBudgetSummaryDialog;
class MortgageSummaryDialog;
class QDate;
class SystemDataSource;
class YearlyBudgetSummaryDialog;
class YearlyIncomeSummaryDialog;

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
    double getMonthlyAdditionalPrincipal() const;
    double getYearlyExpenseTotal() const;
    double getYearlyIncomeTotal() const;
    double getYearlyInvestmentTotal() const;
    double getYearlyCashSavedTotal() const;
    double getYearlyAmountSaved() const;
    double getYearlySavingsRatio() const;
    double getYearlyAdditionalPrincipal() const;
    double getMonthlyRemainingBudget() const;
    std::vector<std::pair<std::string, double>> getInvestmentTypesAndYearlyTotals() const;
    std::string getRatioForPieChart(double amount) const;
    double getYearlyExpenditureRatio() const;

    // Supporting functions for Main Window auxilary actions
    void showYearlyBudgetSummaryDialog(QWidget* parent);
    void showMonthlyBudgetSummaryDialog(QWidget* parent);
    void showFoodExpensesDialog(QWidget* parent);
    void showMiscExpensesDialog(QWidget* parent);
    void showYearlyIncomeSummaryDialog(QWidget* parent);
    void showAutomaticMonthlyPaymentSummaryDialog(QWidget* parent);
    void showAssetSummaryDialog(QWidget* parent);
    void showMortgageSummaryDialog(QWidget* parent);
    void showAddExpenseTransactionDialog(QWidget* parent);

private:
    SystemDataSource& sds;

    std::unique_ptr<YearlyBudgetSummaryDialog> yearlyBudgetDialog;
    std::unique_ptr<MonthlyBudgetSummaryDialog> monthlyBudgetDialog;
    std::unique_ptr<ExpenseTypeSummaryDialog> foodExpensesDialog;
    std::unique_ptr<ExpenseTypeSummaryDialog> miscExpensesDialog;
    std::unique_ptr<YearlyIncomeSummaryDialog> yearlyIncomeDialog;
    std::unique_ptr<AutomaticMonthlyPaymentSummaryDialog> automaticMonthlyPaymentDialog;
    std::unique_ptr<AssetSummaryDialog> assetSummaryDialog;
    std::unique_ptr<MortgageSummaryDialog> mortgageSummaryDialog;
    std::unique_ptr<AddExpenseTransactionDialog> addExpenseTransactionDialog;

    int currentYear = 0;
    int currentMonth = 0;
};

#endif // MAINWINDOWCONTROLLER_H
