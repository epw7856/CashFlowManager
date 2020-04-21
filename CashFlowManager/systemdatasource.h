#ifndef SYSTEMDATASOURCE_H
#define SYSTEMDATASOURCE_H

#include "expenseinterface.h"
#include "investmentinterface.h"
#include <QJsonObject>

class ExpenseType;

class SystemDataSource
:
    public ExpenseInterface,
    public InvestmentInterface
{
public:
    SystemDataSource() {}

    // Expense Interface
    std::vector<ExpenseType> getExpenseTypes() const override;
    std::set<ExpenseTransaction> getExpenseTransactions() const override;
    std::set<ExpenseTransaction> getExpenseTransactionsByTimePeriod(QDate startingPeriod, QDate endingPeriod) const override;

    // Investment Interface


    void loadSystemConfig(std::string filePath);

private:
    std::vector<ExpenseType> expenseTypes = {};
    std::set<ExpenseTransaction> expenseTransactionList = {};

    void parseExpenseTypes(const QJsonObject& obj);
    void parseExpenseList(const QJsonObject& obj);

};

#endif // SYSTEMDATASOURCE_H
