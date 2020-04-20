#ifndef SYSTEMDATASOURCE_H
#define SYSTEMDATASOURCE_H

#include "expenseinterface.h"
#include <memory>
#include <QJsonObject>
#include <set>
#include <string>
#include <vector>

class ExpenseEntry;
class ExpenseType;

class SystemDataSource : public ExpenseInterface
{
public:
    SystemDataSource() {}

    // Expense Interface
    std::vector<std::shared_ptr<ExpenseType>> getExpenseTypes() const override;
    std::set<std::shared_ptr<ExpenseEntry>> getExpenseList() const override;
    std::set<std::shared_ptr<ExpenseEntry>> getExpenseListByTimePeriod(QDate startingPeriod, QDate endingPeriod) const override;

    void loadSystemConfig(std::string filePath);

private:
    std::vector<std::shared_ptr<ExpenseType>> expenseTypes = {};
    std::set<std::shared_ptr<ExpenseEntry>> expenseList = {};

    void parseExpenseTypes(const QJsonObject& obj);
    void parseExpenseList(const QJsonObject& obj);
};

#endif // SYSTEMDATASOURCE_H
