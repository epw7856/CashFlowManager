#include "currencyutilities.h"
#include "dateutilities.h"
#include "expenseinterface.h"
#include "monthlyexpensetablemodel.h"
#include "expensetype.h"
#include <QBrush>
#include <QColor>

MonthlyExpenseTableModel::MonthlyExpenseTableModel(ExpenseInterface& localExpenseInterface)
:
    expenseInterface(localExpenseInterface),
    numColumns(4)
{
    std::pair<QDate, QDate> dates = DateUtilities::getCurrentMonthDates();
    startDatePeriod = dates.first;
    endDatePeriod = dates.second;
}

int MonthlyExpenseTableModel::rowCount(const QModelIndex&) const
{
    return static_cast<int>(expenseTypes.size());
}

int MonthlyExpenseTableModel::columnCount(const QModelIndex&) const
{
    return numColumns;
}

QVariant MonthlyExpenseTableModel::data(const QModelIndex& index, int role) const
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
                return QString::fromStdString(CurrencyUtilities::formatCurrency(expenseInterface.getMonthlyBudgetByType(expenseTypes[rowUint]->getName())));
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
                double remaining = expenseInterface.getMonthlyBudgetByType(expenseTypes[rowUint]->getName()) - expenseInterface.getExpenseTransactionsTotalByTimePeriod(expenseTypes[rowUint]->getName(),
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

    if(role == Qt::BackgroundRole)
    {
        int numRows = rowCount(index);
        if(index.row() < numRows)
        {
            double actual = CurrencyUtilities::formatCurrencyToDouble(index.sibling(index.row(), 2).data().toString().toStdString());
            double remaining = CurrencyUtilities::formatCurrencyToDouble(index.sibling(index.row(), 3).data().toString().toStdString());

            if((actual > 0) && (remaining == 0))
            {
                return QVariant(QBrush(QColor(Qt::green)));
            }
            else if((actual > 0) && (remaining < 0))
            {
                return QVariant(QBrush(QColor(Qt::red)));
            }
        }
    }

    return {};
}

QVariant MonthlyExpenseTableModel::headerData(int section, Qt::Orientation orientation, int role) const
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

void MonthlyExpenseTableModel::setExpenseTypes(const std::vector<ExpenseType*>& localExpenseTypes)
{
    expenseTypes = localExpenseTypes;
}
