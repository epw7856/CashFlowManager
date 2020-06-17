#ifndef SYSTEMDATASOURCE_H
#define SYSTEMDATASOURCE_H

#include "assetinterface.h"
#include "expenseinterface.h"
#include "incomeinterface.h"
#include "investmentinterface.h"
#include <memory>
#include "mortgageinterface.h"
#include <QFile>
#include <QJsonObject>
#include "transactioncomparison.h"

class MortgageInformation;

class SystemDataSource
:
    public ExpenseInterface,
    public InvestmentInterface,
    public IncomeInterface,
    public AssetInterface,
    public MortgageInterface
{
public:
    SystemDataSource(const std::string& filePath);
    ~SystemDataSource() override;
    bool saveSystemConfig();

    // Expense Interface
    std::vector<ExpenseType*> getExpenseTypes() const override;
    void deleteExpenseType(const std::string& expenseType) override;
    void updateExpenseType(const std::string& currentName, const std::string& updatedName, double monthlyBudget) override;
    std::vector<ExpenseTransaction*> getExpenseTransactionsByTimePeriod(const std::string& expenseType, const QDate& startingPeriod, const QDate& endingPeriod) const override;
    double getExpenseTransactionsTotalByTimePeriod(const std::string& expenseType, const QDate& startingPeriod, const QDate& endingPeriod) const override;
    std::vector<AutomaticMonthlyPayment*> getAutomaticMonthlyPayments() const override;
    double getAutomaticMonthlyPaymentsTotal() const override;
    void addExpenseType(const ExpenseType& type) override;
    void addExpenseTransactionByType(const std::string& expenseType, const ExpenseTransaction& transaction) override;
    void addAutomaticMonthlyPayment(const AutomaticMonthlyPayment& payment) override;
    double getMonthlyExpenseTotal(int year, int month) const override;
    double getMonthlyBudgetTotal(int month) const override;
    double getYearlyExpenseTotal(int year) const override;
    double getMonthlyBudgetByType(const std::string& expenseType, int month) const override;

    // Investment Interface
    std::vector<InvestmentType*> getInvestmentTypes() const override;
    std::vector<InvestmentTransaction*> getInvestmentTransactionsByTimePeriod(const std::string& investmentType, const QDate& startingPeriod, const QDate& endingPeriod) const override;
    double getInvestmentTransactionsTotalByTimePeriod(const std::string& investmentType, const QDate& startingPeriod, const QDate& endingPeriod) const override;
    void addInvestmentType(const InvestmentType& type) override;
    void addInvestmentTransactionByType(const std::string& investmentType, const InvestmentTransaction& transaction) override;
    double getMonthlyInvestmentTotal(int year, int month) const override;
    double getYearlyInvestmentTotal(int year) const override;
    double getMonthlyInvestmentTargetTotal() const override;

    // Income Interface
    std::vector<SalaryIncome*> getSalaryIncomeTransactionsByTimePeriod(const QDate& startingPeriod, const QDate& endingPeriod) const override;
    std::vector<SupplementalIncome*> getSupplementalIncomeTransactionsByTimePeriod(const QDate& startingPeriod, const QDate& endingPeriod) const override;
    double getTotalIncomeTotalByTimePeriod(const QDate& startingPeriod, const QDate& endingPeriod) const override;
    double getSalaryIncomeTotalByTimePeriod(const QDate& startingPeriod, const QDate& endingPeriod) const override;
    double getSupplementalIncomeTotalByTimePeriod(const QDate& startingPeriod, const QDate& endingPeriod) const override;
    void addSalaryPayment(const SalaryIncome& payment) override;
    void addSupplementalPayment(const SupplementalIncome& payment) override;
    double getMonthlyIncomeTotal(int year, int month) const override;
    double getYearlyIncomeTotal(int year) const override;
    int getYearlyOvertimeTotal() const override;

    // Asset Interface
    std::vector<AssetEntry*> getAssetList() const override;
    std::vector<AssetEntry*> getAssetListByType(AssetType type) const override;
    void addAsset(const AssetEntry& entry) override;
    void addAssetValue(const std::string& assetName, const std::pair<QDate, double>& valueEntry) override;
    double getAssetValue(const std::string assetName, int year, int month) const override;
    double getAssetTotalValueByType(AssetType type, int year, int month) const override;
    bool currentMonthValuesEntered() const override;

    // Mortgage Interface
    double getTotalLoanAmount() const override;
    double getMarketValue() const override;
    double getInterestRate() const override;
    int getLoanTerm() const override;
    double getBasePayment() const override;
    QDate getLoanStartDate() const override;
    double getPurchasePrice() const override;
    double getAdditionalPrincipalPaymentTotalByDate(const QDate& startingPeriod, const QDate& endingPeriod) const override;
    bool mortgagePaidForMonth(int year, int month) const override;
    void addAdditionalPrincipalPayment(const MortgagePrincipalPayment& payment) override;

private:
    QFile systemConfigFile;
    QJsonObject obj;

    std::vector<std::unique_ptr<ExpenseType>> expenseTypes;
    std::vector<std::unique_ptr<InvestmentType>> investmentTypes;
    std::vector<std::unique_ptr<AutomaticMonthlyPayment>> automaticMonthlyPaymentList;
    std::multiset<std::unique_ptr<SalaryIncome>, TransactionComparison<SalaryIncome>> salaryIncomeList;
    std::multiset<std::unique_ptr<SupplementalIncome>, TransactionComparison<SupplementalIncome>> supplementalIncomeList;
    std::vector<std::unique_ptr<AssetEntry>> assetList;
    std::unique_ptr<MortgageInformation> mortgageInfo;

    // Helper functions for JSON data parsing
    bool loadSystemConfig();
    void createSystemConfigurationTemplate();
    void parseExpenseTypes();
    void parseInvestmentTypes();
    void parseAutomaticMonthlyPayments();
    void parseSalaryIncome();
    void parseSupplementalIncome();
    void parseAssetList();
    void parseMortgageInformation();

    // Template functions to query for types, transactions, and transaction totals
    template<typename Transaction>
    std::vector<Transaction*> getTransactionsByTimePeriod(const std::multiset<std::unique_ptr<Transaction>, TransactionComparison<Transaction>>& set, const QDate& startingPeriod, const QDate& endingPeriod) const;

    template<typename Transaction>
    double getTransactionsTotalByTimePeriod(const std::multiset<std::unique_ptr<Transaction>, TransactionComparison<Transaction>>& set, const QDate& startingPeriod, const QDate& endingPeriod) const;

    template<typename Type>
    typename std::vector<std::unique_ptr<Type>>::const_iterator findMatchingType(const std::vector<std::unique_ptr<Type>>& list, const std::string& name) const;
};

#endif // SYSTEMDATASOURCE_H
