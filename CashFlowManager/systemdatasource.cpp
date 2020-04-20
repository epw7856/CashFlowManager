#include "systemdatasource.h"

std::vector<std::shared_ptr<ExpenseType> > SystemDataSource::getExpenseTypes() const
{
    return expenseTypes;
}

std::set<std::shared_ptr<ExpenseEntry> > SystemDataSource::getExpenseList() const
{
    return expenseList;
}

std::set<std::shared_ptr<ExpenseEntry> > SystemDataSource::getExpenseListByTimePeriod(QDateTime period) const
{
    return {};
}

void SystemDataSource::loadSystemConfig(std::string filePath)
{

}
