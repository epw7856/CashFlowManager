#ifndef SYSTEMDATASOURCE_H
#define SYSTEMDATASOURCE_H

#include "assetinterface.h"
#include "expenseinterface.h"
#include "incomeinterface.h"
#include "investmentinterface.h"
#include <memory>
#include <QJsonObject>

class MortgageInformation;

class SystemDataSource
:
    public ExpenseInterface,
    public InvestmentInterface,
    public IncomeInterface,
    public AssetInterface
{
public:
    SystemDataSource();
    ~SystemDataSource() override;
    void loadSystemConfig(std::string filePath);

    // Expense Interface
    std::vector<ExpenseType*> getExpenseTypes() const override;
    std::multiset<ExpenseTransaction*> getExpenseTransactions() const override;
    std::multiset<ExpenseTransaction*> getExpenseTransactionsByTimePeriod(QDate startingPeriod, QDate endingPeriod) const override;
    std::vector<AutomaticMonthlyPayment*> getAutomaticMonthlyPayments() const override;

    // Investment Interface
    std::vector<InvestmentType*> getInvestmentTypes() const override;
    std::multiset<InvestmentTransaction*> getInvestmentTransactions() const override;
    std::multiset<InvestmentTransaction*> getInvestmentTransactionsByTimePeriod(QDate startingPeriod, QDate endingPeriod) const override;

    // Income Interface
    std::multiset<SalaryIncome*> getSalaryIncomeTransactionsByTimePeriod(QDate startingPeriod, QDate endingPeriod) const override;
    std::multiset<SupplementalIncome*> getSupplementalIncomeTransactionsByTimePeriod(QDate startingPeriod, QDate endingPeriod) const override;
    double getTotalIncomeByTimePeriod(QDate startingPeriod, QDate endingPeriod) const override;
    double getSalaryIncomeByTimePeriod(QDate startingPeriod, QDate endingPeriod) const override;

    // Asset Interface
    std::vector<AssetEntry*> getAssetList() const override;
    std::vector<AssetEntry*> getAssetListByType(AssetType type) const override;

private:
    std::vector<std::unique_ptr<ExpenseType>> expenseTypes;
    std::multiset<std::unique_ptr<ExpenseTransaction>> expenseTransactionList;
    std::vector<std::unique_ptr<InvestmentType>> investmentTypes;
    std::multiset<std::unique_ptr<InvestmentTransaction>> investmentTransactionList;
    std::vector<std::unique_ptr<AutomaticMonthlyPayment>> automaticMonthlyPaymentList;
    std::multiset<std::unique_ptr<SalaryIncome>> salaryIncomeList;
    std::multiset<std::unique_ptr<SupplementalIncome>> supplementalIncomeList;
    std::vector<std::unique_ptr<AssetEntry>> assetList;
    std::unique_ptr<MortgageInformation> mortgageInfo;

    void parseExpenseTypes(const QJsonObject& obj);
    void parseExpenseTransactionList(const QJsonObject& obj);
    void parseInvestmentTypes(const QJsonObject& obj);
    void parseInvestmentTransactionList(const QJsonObject& obj);
    void parseAutomaticMonthlyPayments(const QJsonObject& obj);
    void parseSalaryIncome(const QJsonObject& obj);
    void parseSupplementalIncome(const QJsonObject& obj);
    void parseAssetList(const QJsonObject& obj);

    std::string assetTypeToString(AssetType type);
    AssetType stringToAssetType(std::string type);
};

#endif // SYSTEMDATASOURCE_H
