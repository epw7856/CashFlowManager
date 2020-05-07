#include "currencyutilities.h"
#include "dateutilities.h"
#include "expenseinterface.h"
#include "expensetablemodel.h"
#include "expensetype.h"

ExpenseTableModel::ExpenseTableModel(ExpenseInterface& localExpenseInterface, std::pair<QDate, QDate> dates)
:
    expenseInterface(localExpenseInterface),
    numColumns(4),
    startDatePeriod(dates.first),
    endDatePeriod(dates.second)
{

}

int ExpenseTableModel::rowCount(const QModelIndex&) const
{
    return static_cast<int>(expenseTypes.size());
}

int ExpenseTableModel::columnCount(const QModelIndex&) const
{
    return numColumns;
}

QVariant ExpenseTableModel::data(const QModelIndex& index, int role) const
{
    if(role == Qt::DisplayRole)
    {
        int numRows = rowCount(index);
        if((index.row() < numRows) && (index.column() < numColumns))
        {
            auto rowUint = static_cast<quint32>(index.row());

            // Expense Type column
            if(index.column() == 0)
            {
                return QString::fromStdString(expenseTypes[rowUint]->getName());
            }
            // Budget column
            else if(index.column() == 1)
            {
                return QString::fromStdString(CurrencyUtilities::formatCurrency(expenseTypes[rowUint]->getMonthlyBudget()));
            }
            // Actual column
            else if(index.column() == 2)
            {
                return QString::fromStdString(CurrencyUtilities::formatCurrency(expenseInterface.getExpenseTransactionsTotalByTimePeriod(expenseTypes[rowUint]->getName(),
                                                                                                                                         startDatePeriod,
                                                                                                                                         endDatePeriod)));
            }
            // Remaining column
            else if(index.column() == 3)
            {
                double remaining = expenseTypes[rowUint]->getMonthlyBudget() - expenseInterface.getExpenseTransactionsTotalByTimePeriod(expenseTypes[rowUint]->getName(),
                                                                                                                                        startDatePeriod,
                                                                                                                                        endDatePeriod);
                return QString::fromStdString(CurrencyUtilities::formatCurrency(remaining));
            }
        }
    }

    if(role == Qt::TextAlignmentRole)
    {
        int numRows = rowCount(index);
        if((index.row() < numRows) && (index.column() < numColumns))
        {
            if(index.column()!= 0)
            {
                return Qt::AlignCenter;
            }
        }
    }

    return {};
}

QVariant ExpenseTableModel::headerData(int section, Qt::Orientation orientation, int role) const
{
    if(role == Qt::DisplayRole)
    {
        if(orientation == Qt::Horizontal)
        {
            if(section == 0)
            {
                return QString("Expense Type");
            }
            else if(section == 1)
            {
                return QString("Budget");
            }
            else if(section == 2)
            {
                return QString("Actual");
            }
            else if(section == 3)
            {
                return QString("Remaining  ");
            }
        }
    }
    return {};
}

void ExpenseTableModel::setExpenseTypes(const std::vector<ExpenseType*>& localExpenseTypes)
{
    expenseTypes = localExpenseTypes;
}
