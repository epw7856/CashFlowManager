#include "currencyutilities.h"
#include "dateutilities.h"
#include "expenseinterface.h"
#include "yearlyexpensetablemodel.h"
#include "expensetype.h"
#include <QBrush>
#include <QColor>

YearlyExpenseTableModel::YearlyExpenseTableModel(ExpenseInterface& localExpenseInterface)
:
    expenseInterface(localExpenseInterface),
    numColumns(3)
{
    std::pair<QDate, QDate> dates = DateUtilities::getCurrentYearDates();
    startDatePeriod = dates.first;
    endDatePeriod = dates.second;
}

int YearlyExpenseTableModel::rowCount(const QModelIndex&) const
{
    return static_cast<int>(expenseTypes.size());
}

int YearlyExpenseTableModel::columnCount(const QModelIndex&) const
{
    return numColumns;
}

QVariant YearlyExpenseTableModel::data(const QModelIndex& index, int role) const
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
            // Spent column
            else if(index.column() == 1)
            {
                return QString::fromStdString(CurrencyUtilities::formatCurrency(expenseInterface.getExpenseTransactionsTotalByTimePeriod(expenseTypes[rowUint]->getName(),
                                                                                                                                         startDatePeriod,
                                                                                                                                         endDatePeriod)));
            }
            // Percentage column
            else if(index.column() == 2)
            {
                double percentage = 100.0 * (expenseInterface.getExpenseTransactionsTotalByTimePeriod(expenseTypes[rowUint]->getName(), startDatePeriod, endDatePeriod) / expenseInterface.getYearlyExpenseTotal());
                return QString::number(percentage, 'f', 2);
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

QVariant YearlyExpenseTableModel::headerData(int section, Qt::Orientation orientation, int role) const
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
                return QString("Spent");
            }
            else if(section == 2)
            {
                return QString("%");
            }
        }
    }
    return {};
}

void YearlyExpenseTableModel::setExpenseTypes()
{
    expenseTypes = expenseInterface.getExpenseTypes();
}
