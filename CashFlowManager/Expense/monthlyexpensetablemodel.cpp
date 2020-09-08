#include "currencyutilities.h"
#include "dateutilities.h"
#include "expenseinterface.h"
#include "monthlyexpensetablemodel.h"
#include "expensetransaction.h"
#include "expensetype.h"
#include <QBrush>
#include <QColor>
#include <QFont>

MonthlyExpenseTableModel::MonthlyExpenseTableModel(ExpenseInterface& localExpenseInterface, int localMonth, bool total)
:
    expenseInterface(localExpenseInterface),
    numColumns(4),
    appendTotalFlag(total),
    month(localMonth)
{
    year = QDate::currentDate().year();
    std::pair<QDate, QDate> dates = DateUtilities::getMonthlyDates(year, month);
    startDatePeriod = dates.first;
    endDatePeriod = dates.second;
}

int MonthlyExpenseTableModel::rowCount(const QModelIndex&) const
{
    return (appendTotalFlag) ? static_cast<int>(expenseTypes.size())+1 : static_cast<int>(expenseTypes.size());
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
        int maxIndex = 0;
        (appendTotalFlag) ? maxIndex = numRows-1 : maxIndex = numRows;

        if((index.row() < maxIndex) && (index.column() < numColumns))
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
                return QString::fromStdString(CurrencyUtilities::formatCurrency(expenseInterface.getMonthlyBudgetByType(expenseTypes[rowUint]->getName(), month)));
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
                double remaining = expenseInterface.getMonthlyBudgetByType(expenseTypes[rowUint]->getName(), month) -
                                   expenseInterface.getExpenseTransactionsTotalByTimePeriod(expenseTypes[rowUint]->getName(), startDatePeriod, endDatePeriod);
                return QString::fromStdString(CurrencyUtilities::formatCurrency(remaining));
            }
        }

        // Total Row
        if(appendTotalFlag)
        {
            if((index.row() == maxIndex) && (index.column() < numColumns))
            {
                // Expense Type column
                if(index.column() == 0)
                {
                    return "Total";
                }
                // Budget column
                else if(index.column() == 1)
                {
                    return QString::fromStdString(CurrencyUtilities::formatCurrency(expenseInterface.getMonthlyBudgetTotal(month)));
                }
                // Actual column
                else if(index.column() == 2)
                {
                    return QString::fromStdString(CurrencyUtilities::formatCurrency(expenseInterface.getMonthlyExpenseTotal(year, month)));
                }
                // Remaining column
                else if(index.column() == 3)
                {
                    return QString::fromStdString(CurrencyUtilities::formatCurrency(expenseInterface.getMonthlyBudgetTotal(month) -
                                                                                    expenseInterface.getMonthlyExpenseTotal(year, month)));
                }
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
            bool requiredExpense = expenseInterface.getExpenseTypeRequiredFlag(index.sibling(index.row(), 0).data().toString().toStdString());

            if(index.row() == numRows - 1)
            {
                if((actual == 0) && (remaining == 0) && (month < QDate::currentDate().month()))
                {
                    return QVariant(QBrush(QColor(Qt::white)));
                }
            }

            if((actual > 0) && (remaining == 0))
            {
                return QVariant(QBrush(QColor(Qt::green)));
            }
            else if((actual >= 0) && (remaining >= 0) && (month < QDate::currentDate().month()) && !requiredExpense)
            {
                return QVariant(QBrush(QColor(Qt::green)));
            }
            else if((actual > 0) && (remaining < 0))
            {
                return QVariant(QBrush(QColor(Qt::red)));
            }
            else
            {
                return QVariant(QBrush(QColor(Qt::white)));
            }
        }
    }

    if((appendTotalFlag) &&
       (role == Qt::FontRole) &&
       (index.row() == rowCount(index)-1))
    {
        QFont font;
        font.setBold(true);
        return font;
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

void MonthlyExpenseTableModel::setExpenseTypes()
{
    expenseTypes = expenseInterface.getExpenseTypes();
}
