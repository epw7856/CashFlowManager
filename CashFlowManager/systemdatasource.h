#ifndef SYSTEMDATASOURCE_H
#define SYSTEMDATASOURCE_H

#include "expenseinterface.h"
#include "investmentinterface.h"
#include <QJsonObject>

class SystemDataSource
:
    public ExpenseInterface,
    public InvestmentInterface
{
public:
    SystemDataSource() {}

    // Expense Interface
    std::vector<ExpenseType> getExpenseTypes() const override;
    std::multiset<ExpenseTransaction> getExpenseTransactions() const override;
    std::multiset<ExpenseTransaction> getExpenseTransactionsByTimePeriod(QDate startingPeriod, QDate endingPeriod) const override;
    std::vector<AutomaticMonthlyPayment> getAutomaticMonthlyPayments() const override;

    // Investment Interface
    std::vector<InvestmentType> getInvestmentTypes() const override;
    std::multiset<InvestmentTransaction> getInvestmentTransactions() const override;
    std::multiset<InvestmentTransaction> getInvestmentTransactionsByTimePeriod(QDate startingPeriod, QDate endingPeriod) const override;

    void loadSystemConfig(std::string filePath);

private:
    std::vector<ExpenseType> expenseTypes = {};
    std::multiset<ExpenseTransaction> expenseTransactionList = {};

    std::vector<InvestmentType> investmentTypes = {};
    std::multiset<InvestmentTransaction> investmentTransactionList = {};

    std::vector<AutomaticMonthlyPayment> automaticMonthlyPaymentList = {};

    void parseExpenseTypes(const QJsonObject& obj);
    void parseExpenseTransactionList(const QJsonObject& obj);
    void parseInvestmentTypes(const QJsonObject& obj);
    void parseInvestmentTransactionList(const QJsonObject& obj);
    void parseAutomaticMonthlyPayments(const QJsonObject& obj);

};

#endif // SYSTEMDATASOURCE_H
