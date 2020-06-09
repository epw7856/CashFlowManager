#include "currencyutilities.h"
#include "dateutilities.h"
#include "expenseinterface.h"
#include "expensetransaction.h"
#include "expensetypetablemodel.h"
#include <QBrush>
#include <QColor>
#include <QFont>

ExpenseTypeTableModel::ExpenseTypeTableModel(ExpenseInterface& localExpenseInterface, std::string localExpenseType, int localMonth)
:
    expenseInterface(localExpenseInterface),
    expenseType(localExpenseType),
    numColumns(4),
    month(localMonth)
{
    std::pair<QDate, QDate> dates = DateUtilities::getMonthlyDates(QDate::currentDate().year(), month);
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

            // Date column
            if(index.column() == 0)
            {
                return expenseTransactions[rowUint]->getDate().toString("MM/dd");
            }
            // Description column
            else if(index.column() == 1)
            {
                return QString::fromStdString(expenseTransactions[rowUint]->getDescription());
            }
            // Amount column
            else if(index.column() == 2)
            {
                return QString::fromStdString(CurrencyUtilities::formatCurrency(expenseTransactions[rowUint]->getAmount()));
            }
            // Remaining column
            else if(index.column() == 3)
            {
                if(rowUint == 0)
                {
                    return QString::fromStdString(CurrencyUtilities::formatCurrency(expenseInterface.getMonthlyBudgetByType(expenseType, month) - expenseTransactions[rowUint]->getAmount()));
                }
                else if(rowUint > 0)
                {
                    double remaining = CurrencyUtilities::formatCurrencyToDouble(index.sibling(index.row() - 1, 3).data().toString().toStdString()) - expenseTransactions[rowUint]->getAmount();
                    //double remaining = 0.0;
                    return QString::fromStdString(CurrencyUtilities::formatCurrency(remaining));
                }

            }
        }

        if((index.row() == numRows - 1) && (index.column() < numColumns))
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
                if(rowCount(index) > 2)
                {
                    return QString::fromStdString(CurrencyUtilities::formatCurrency(CurrencyUtilities::formatCurrencyToDouble(index.sibling(index.row() - 2, 3).data().toString().toStdString())));
                }
                else
                {
                    return QString::fromStdString(CurrencyUtilities::formatCurrency(expenseInterface.getMonthlyBudgetByType(expenseType, month)));
                }

            }
        }
    }

    if(role == Qt::BackgroundRole)
    {
        int numRows = rowCount(index);
        if(index.row() == numRows - 1)
        {
            double remaining = CurrencyUtilities::formatCurrencyToDouble(index.sibling(index.row(), 3).data().toString().toStdString());

            if((remaining >= 0) && (month < QDate::currentDate().month()))
            {
                return QVariant(QBrush(QColor(Qt::green)));
            }
            else if(remaining < 0)
            {
                return QVariant(QBrush(QColor(Qt::red)));
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
