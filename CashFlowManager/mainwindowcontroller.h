#ifndef MAINWINDOWCONTROLLER_H
#define MAINWINDOWCONTROLLER_H

#include <memory>
#include <QObject>
#include <string>
#include <vector>

class AddExpenseTransactionDialog;
class AddExpenseTypeDialog;
class AddIncomeTransactionDialog;
class AddInvestmentTransactionDialog;
class AddInvestmentTypeDialog;
class AssetSummaryDialog;
class AutomaticMonthlyPaymentSummaryDialog;
class ExpenseTypeSummaryDialog;
class ExpenseTypeSelectDialog;
class MonthlyBudgetSummaryDialog;
class MortgageSummaryDialog;
class QDate;
class SystemDataSource;
class UpdateAssetInfoDialog;
class UpdateAutomaticMonthlyPaymentsDialog;
class UpdateMortgageInfoDialog;
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
    bool monthlyBudgetExists() const;
    bool expenseTypesExist() const;
    bool investmentTypesExist() const;
    bool isCurrentMonthOverBudget() const;
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

    // Supporting functions for Main Window auxilary actions
    void showYearlyBudgetSummaryDialog(QWidget* parent);
    void showExpenseTypeSelectionDialog(QWidget* parent);
    void showMonthlyBudgetSummaryDialog(QWidget* parent);
    void showYearlyIncomeSummaryDialog(QWidget* parent);
    void showAutomaticMonthlyPaymentSummaryDialog(QWidget* parent);
    void showAssetSummaryDialog(QWidget* parent);
    void showMortgageSummaryDialog(QWidget* parent);
    void showAddExpenseTransactionDialog(QWidget* parent);
    void showAddExpenseTypeDialog(QWidget* parent);
    void showModifyExpenseTypeDialog(QWidget* parent);
    void showAddInvestmentTransactionDialog(QWidget* parent);
    void showAddInvestmentTypeDialog(QWidget* parent);
    void showModifyInvestmentTypeDialog(QWidget* parent);
    void showAddIncomeTransactionDialog(QWidget* parent);
    void showUpdateAutomaticMonthlyPaymentDialog(QWidget* parent);
    void showUpdateAssetInfoDialog(QWidget* parent);
    void showAddAssetDialog(QWidget* parent);
    void showUpdateMortgageInfoDialog(QWidget* parent);

signals:
    void requestMainWindowUpdate();

public slots:
    void showMonthlyBudgetExpenseTypeSummaryDialog(QString type, QWidget* parent);
    void dialogCloseEvent();

private:
    SystemDataSource& sds;

    std::unique_ptr<YearlyBudgetSummaryDialog> yearlyBudgetDialog;
    std::unique_ptr<MonthlyBudgetSummaryDialog> monthlyBudgetDialog;
    std::unique_ptr<ExpenseTypeSelectDialog> expenseTypeSelectDialog;
    std::unique_ptr<ExpenseTypeSummaryDialog> expenseTypeSummaryDialog;
    std::unique_ptr<YearlyIncomeSummaryDialog> yearlyIncomeDialog;
    std::unique_ptr<AutomaticMonthlyPaymentSummaryDialog> automaticMonthlyPaymentDialog;
    std::unique_ptr<AssetSummaryDialog> assetSummaryDialog;
    std::unique_ptr<MortgageSummaryDialog> mortgageSummaryDialog;
    std::unique_ptr<AddExpenseTransactionDialog> addExpenseTransactionDialog;
    std::unique_ptr<AddExpenseTypeDialog> addExpenseTypeDialog;
    std::unique_ptr<AddExpenseTypeDialog> modifyExpenseTypeDialog;
    std::unique_ptr<AddInvestmentTransactionDialog> addInvestmentTransactionDialog;
    std::unique_ptr<AddInvestmentTypeDialog> addInvestmentTypeDialog;
    std::unique_ptr<AddInvestmentTypeDialog> modifyInvestmentTypeDialog;
    std::unique_ptr<AddIncomeTransactionDialog> addIncomeTransactionDialog;
    std::unique_ptr<UpdateAutomaticMonthlyPaymentsDialog> updateAutomaticMonthlyPaymentsDialog;
    std::unique_ptr<UpdateAssetInfoDialog> updateAssetInfoDialog;
    std::unique_ptr<UpdateAssetInfoDialog> addAssetInfoDialog;
    std::unique_ptr<UpdateMortgageInfoDialog> updateMortgageInfoDialog;

    int currentYear = 0;
    int currentMonth = 0;
};

#endif // MAINWINDOWCONTROLLER_H
