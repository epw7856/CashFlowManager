#ifndef SYSTEMDATASOURCE_H
#define SYSTEMDATASOURCE_H

#include "assetinterface.h"
#include "expenseinterface.h"
#include "incomeinterface.h"
#include "investmentinterface.h"
#include <QJsonObject>
#include "salaryincome.h"
#include "supplementalincome.h"

class SystemDataSource
:
    public ExpenseInterface,
    public InvestmentInterface,
    public IncomeInterface,
    public AssetInterface
{
public:
    SystemDataSource() {}
    void loadSystemConfig(std::string filePath);

    // Expense Interface
    std::vector<ExpenseType> getExpenseTypes() const override;
    std::multiset<ExpenseTransaction> getExpenseTransactions() const override;
    std::multiset<ExpenseTransaction> getExpenseTransactionsByTimePeriod(QDate startingPeriod, QDate endingPeriod) const override;
    std::vector<AutomaticMonthlyPayment> getAutomaticMonthlyPayments() const override;

    // Investment Interface
    std::vector<InvestmentType> getInvestmentTypes() const override;
    std::multiset<InvestmentTransaction> getInvestmentTransactions() const override;
    std::multiset<InvestmentTransaction> getInvestmentTransactionsByTimePeriod(QDate startingPeriod, QDate endingPeriod) const override;

    // Income Interface
    double getTotalIncomeByTimePeriod(QDate startingPeriod, QDate endingPeriod) const override;
    double getSalaryIncomeByTimePeriod(QDate startingPeriod, QDate endingPeriod) const override;

    // Asset Interface
    std::vector<AssetEntry> getAssetList() const override;
    std::vector<AssetEntry> getAssetListByType(AssetType type) const override;

private:
    std::vector<ExpenseType> expenseTypes = {};
    std::multiset<ExpenseTransaction> expenseTransactionList = {};
    std::vector<InvestmentType> investmentTypes = {};
    std::multiset<InvestmentTransaction> investmentTransactionList = {};
    std::vector<AutomaticMonthlyPayment> automaticMonthlyPaymentList = {};
    std::multiset<SalaryIncome> salaryIncomeList = {};
    std::multiset<SupplementalIncome> supplementalIncomeList = {};
    std::vector<AssetEntry> assetList = {};

    void parseExpenseTypes(const QJsonObject& obj);
    void parseExpenseTransactionList(const QJsonObject& obj);
    void parseInvestmentTypes(const QJsonObject& obj);
    void parseInvestmentTransactionList(const QJsonObject& obj);
    void parseAutomaticMonthlyPayments(const QJsonObject& obj);
    void parseSalaryIncome(const QJsonObject& obj);
    void parseSupplementalIncome(const QJsonObject& obj);
    void parseAssetList(const QJsonObject& obj);

    AssetType stringToAssetType(const std::string& type);
};

#endif // SYSTEMDATASOURCE_H
