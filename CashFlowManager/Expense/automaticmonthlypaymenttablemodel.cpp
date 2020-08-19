#include "automaticmonthlypayment.h"
#include "automaticmonthlypaymenttablemodel.h"
#include "currencyutilities.h"
#include "expenseinterface.h"
#include <QFont>

AutomaticMonthlyPaymentTableModel::AutomaticMonthlyPaymentTableModel(ExpenseInterface& localExpenseInterface)
:
    expenseInterface(localExpenseInterface),
    numColumns(3)
{

}

int AutomaticMonthlyPaymentTableModel::rowCount(const QModelIndex&) const
{
    return static_cast<int>(automaticMonthlyPayments.size()) + 2;
}

int AutomaticMonthlyPaymentTableModel::columnCount(const QModelIndex&) const
{
    return numColumns;
}

QVariant AutomaticMonthlyPaymentTableModel::data(const QModelIndex& index, int role) const
{
    if(role == Qt::DisplayRole)
    {
        int numRows = rowCount(index);
        if((index.row() < numRows - 2) && (index.column() < numColumns))
        {
            auto rowUint = static_cast<quint32>(index.row());

            // Account column
            if(index.column() == 0)
            {
                return QString::fromStdString(automaticMonthlyPayments[rowUint]->getAccount());
            }
            // Description column
            else if(index.column() == 1)
            {
                return QString::fromStdString(automaticMonthlyPayments[rowUint]->getName());
            }
            // Amount column
            else if(index.column() == 2)
            {
                return QString::fromStdString(CurrencyUtilities::formatCurrency(automaticMonthlyPayments[rowUint]->getAmount()));
            }
        }

        if((index.row() == numRows - 1) && (index.column() < numColumns))
        {
            // Account column
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
                return QString::fromStdString(CurrencyUtilities::formatCurrency(expenseInterface.getAutomaticMonthlyPaymentsTotal()));
            }
        }
    }

    if(role == Qt::TextAlignmentRole)
    {
        int numRows = rowCount(index);
        if((index.row() < numRows) && (index.column() < numColumns))
        {
            if(index.column() != 0)
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

QVariant AutomaticMonthlyPaymentTableModel::headerData(int section, Qt::Orientation orientation, int role) const
{
    if(role == Qt::DisplayRole)
    {
        if(orientation == Qt::Horizontal)
        {
            if(section == 0)
            {
                return QString("Account");
            }
            else if(section == 1)
            {
                return QString("Description");
            }
            else if(section == 2)
            {
                return QString("Amount");
            }
        }
    }

    return {};
}

void AutomaticMonthlyPaymentTableModel::setAutomaticMonthlyPayments()
{
    automaticMonthlyPayments = expenseInterface.getAutomaticMonthlyPayments();
}
