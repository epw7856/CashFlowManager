#ifndef SYSTEMDATASOURCE_H
#define SYSTEMDATASOURCE_H

#include "Expense/expenseinterface.h"
#include <memory>
#include <set>
#include <string>
#include <vector>

class ExpenseEntry;
class ExpenseType;

class SystemDataSource : public ExpenseInterface
{
public:
    SystemDataSource() {}
    std::vector<std::shared_ptr<ExpenseType>> getExpenseTypes() const override;
    std::set<std::shared_ptr<ExpenseEntry>> getExpenseList() const override;
    std::set<std::shared_ptr<ExpenseEntry>> getExpenseListByTimePeriod(QDateTime period) const override;

    void loadSystemConfig(std::string filePath);

private:
    std::vector<std::shared_ptr<ExpenseType>> expenseTypes = {};
    std::set<std::shared_ptr<ExpenseEntry>> expenseList = {};
};

#endif // SYSTEMDATASOURCE_H
