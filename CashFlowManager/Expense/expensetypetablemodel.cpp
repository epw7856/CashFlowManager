#include "currencyutilities.h"
#include "dateutilities.h"
#include "expenseinterface.h"
#include "expensetransaction.h"
#include "expensetypetablemodel.h"
#include <QFont>

ExpenseTypeTableModel::ExpenseTypeTableModel(ExpenseInterface& localExpenseInterface, std::string localExpenseType, int localMonth)
:
    expenseInterface(localExpenseInterface),
    expenseType(localExpenseType),
    numColumns(4),
    month(localMonth)
{
    std::pair<QDate, QDate> dates = DateUtilities::getMonthlyDates(month);
    startDatePeriod = dates.first;
    endDatePeriod = dates.second;
}

int ExpenseTypeTableModel::rowCount(const QModelIndex&) const
{
    return static_cast<int>(expenseTransactions.size()) + 2;
}

int ExpenseTypeTableModel::columnCount(const QModelIndex&) const
{
    return numColumns;
}

QVariant ExpenseTypeTableModel::data(const QModelIndex& index, int role) const
{
    if(role == Qt::DisplayRole)
    {
        int numRows = rowCount(index);
        if((index.row() < numRows - 2) && (index.column() < numColumns))
        {
            auto rowUint = static_cast<quint32>(index.row());

            std::multiset<ExpenseTransaction*>::iterator itr = expenseTransactions.begin();
            std::advance(itr, rowUint);

            // Date column
            if(index.column() == 0)
            {
                return (*itr)->getDate().toString("MM/dd/yyyy");
            }
            // Description column
            else if(index.column() == 1)
            {
                return QString::fromStdString((*itr)->getDescription());
            }
            // Amount column
            else if(index.column() == 2)
            {
                return QString::fromStdString(CurrencyUtilities::formatCurrency((*itr)->getAmount()));
            }
            // Remaining column
            else if(index.column() == 3)
            {
                if(rowUint == 0)
                {
                    return QString::fromStdString(CurrencyUtilities::formatCurrency(expenseInterface.getMonthlyBudgetByType(expenseType, month) - (*itr)->getAmount()));
                }
                else
                {
                    double remaining = index.sibling(index.row() - 1, 3).data().toDouble() - (*itr)->getAmount();
                    return QString::fromStdString(CurrencyUtilities::formatCurrency(remaining));
                }

            }
        }

        if((index.row() == numRows-2) && (index.column() < numColumns))
        {
            return "";
        }

        if((index.row() == numRows-1) && (index.column() < numColumns))
        {
            // Date column
            if(index.column() == 0)
            {
                return "";
            }
            // Description column
            else if(index.column() == 1)
            {
                return "Total";
            }
            // Amount column
            else if(index.column() == 2)
            {
                return QString::fromStdString(CurrencyUtilities::formatCurrency(expenseInterface.getExpenseTransactionsTotalByTimePeriod(expenseType,
                                                                                                                                         startDatePeriod,
                                                                                                                                         endDatePeriod)));
            }
            // Remaining column
            else if(index.column() == 3)
            {
                return QString::fromStdString(CurrencyUtilities::formatCurrency(index.sibling(index.row() - 2, 3).data().toDouble()));
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

    if((role == Qt::FontRole) && (index.row() == rowCount(index)-1))
    {
        QFont font;
        font.setBold(true);
        return font;
    }

    return {};
}

QVariant ExpenseTypeTableModel::headerData(int section, Qt::Orientation orientation, int role) const
{
    if(role == Qt::DisplayRole)
    {
        if(orientation == Qt::Horizontal)
        {
            if(section == 0)
            {
                return QString("Date");
            }
            else if(section == 1)
            {
                return QString("Description");
            }
            else if(section == 2)
            {
                return QString("Amount");
            }
            else if(section == 3)
            {
                return QString("Remaining  ");
            }
        }
    }

    return {};
}

void ExpenseTypeTableModel::setExpenseTransactions()
{
    expenseTransactions = expenseInterface.getExpenseTransactionsByTimePeriod(expenseType, startDatePeriod, endDatePeriod);
}
