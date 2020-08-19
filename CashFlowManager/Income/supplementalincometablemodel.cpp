#include "currencyutilities.h"
#include "dateutilities.h"
#include "incomeinterface.h"
#include <QBrush>
#include <QFont>
#include "supplementalincome.h"
#include "supplementalincometablemodel.h"

SupplementalIncomeTableModel::SupplementalIncomeTableModel(IncomeInterface &localIncomeInterface, int localYear)
:
    incomeInterface(localIncomeInterface),
    numColumns(3),
    year(localYear)
{
    std::pair<QDate, QDate> dates = DateUtilities::getYearlyDates(year);
    startDatePeriod = dates.first;
    endDatePeriod = dates.second;
}

int SupplementalIncomeTableModel::rowCount(const QModelIndex&) const
{
    return static_cast<int>(supplementalIncomeTransactions.size()) + 2;
}

int SupplementalIncomeTableModel::columnCount(const QModelIndex&) const
{
    return numColumns;
}

QVariant SupplementalIncomeTableModel::data(const QModelIndex& index, int role) const
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
                return supplementalIncomeTransactions[rowUint]->getDate().toString("MM/dd");
            }
            // Description column
            else if(index.column() == 1)
            {
                return QString::fromStdString(supplementalIncomeTransactions[rowUint]->getDescription());
            }
            // Amount column
            else if(index.column() == 2)
            {
                return QString::fromStdString(CurrencyUtilities::formatCurrency(supplementalIncomeTransactions[rowUint]->getAmount()));
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
                return QString::fromStdString(CurrencyUtilities::formatCurrency(incomeInterface.getSupplementalIncomeTotalByTimePeriod(startDatePeriod,
                                                                                                                                       endDatePeriod)));
            }
        }
    }

    if(role == Qt::TextAlignmentRole)
    {
        int numRows = rowCount(index);
        if((index.row() < numRows) && (index.column() < numColumns))
        {
            if(index.column() == 1)
            {
                return Qt::AlignLeft;
            }
            else
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

QVariant SupplementalIncomeTableModel::headerData(int section, Qt::Orientation orientation, int role) const
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
                return QString("Amount  ");
            }
        }
    }

    return {};
}

void SupplementalIncomeTableModel::setSupplementalIncomeTransactions()
{
    supplementalIncomeTransactions = incomeInterface.getSupplementalIncomeTransactionsByTimePeriod(startDatePeriod,
                                                                                                   endDatePeriod);
}
