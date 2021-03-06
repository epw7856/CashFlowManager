#include "currencyutilities.h"
#include "dateutilities.h"
#include "investmentinterface.h"
#include "yearlyinvestmenttablemodel.h"
#include "investmenttype.h"
#include <QBrush>
#include <QColor>

YearlyInvestmentTableModel::YearlyInvestmentTableModel(InvestmentInterface& localInvestmentInterface)
:
    investmentInterface(localInvestmentInterface),
    numColumns(3)
{
    std::pair<QDate, QDate> dates = DateUtilities::getCurrentYearDates();
    startDatePeriod = dates.first;
    endDatePeriod = dates.second;
}

int YearlyInvestmentTableModel::rowCount(const QModelIndex&) const
{
    return static_cast<int>(investmentTypes.size());
}

int YearlyInvestmentTableModel::columnCount(const QModelIndex&) const
{
    return numColumns;
}

QVariant YearlyInvestmentTableModel::data(const QModelIndex& index, int role) const
{
    int numRows = rowCount(index);
    if((index.row() < numRows) && (index.column() < numColumns))
    {
        auto rowUint = static_cast<quint32>(index.row());

        // Investment Type column
        if(index.column() == 0)
        {
            if(role == Qt::DisplayRole || role == Qt::EditRole)
            {
                return QString::fromStdString(investmentTypes[rowUint]->getName());
            }
        }
        // Invested column
        else if(index.column() == 1)
        {
            double amount = investmentInterface.getInvestmentTransactionsTotalByTimePeriod(investmentTypes[rowUint]->getName(),
                                                                                           startDatePeriod,
                                                                                           endDatePeriod);
            if(role == Qt::DisplayRole)
            {
                return QString::fromStdString(CurrencyUtilities::formatCurrency(amount));
            }
            else if(role == Qt::EditRole)
            {
                return amount;
            }
        }
        // Percentage column
        else if(index.column() == 2)
        {
            double percentage = 100.0 * (investmentInterface.getInvestmentTransactionsTotalByTimePeriod(investmentTypes[rowUint]->getName(),
                                                                                                        startDatePeriod, endDatePeriod) / investmentInterface.getYearlyInvestmentTotal(QDate::currentDate().year()));
            if(role == Qt::DisplayRole)
            {
                return QString::number(percentage, 'f', 2);
            }
            else if(role == Qt::EditRole)
            {
                return percentage;
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

QVariant YearlyInvestmentTableModel::headerData(int section, Qt::Orientation orientation, int role) const
{
    if(role == Qt::DisplayRole)
    {
        if(orientation == Qt::Horizontal)
        {
            if(section == 0)
            {
                return QString("Investment Type");
            }
            else if(section == 1)
            {
                return QString("Invested");
            }
            else if(section == 2)
            {
                return QString("%");
            }
        }
    }
    return {};
}

void YearlyInvestmentTableModel::setInvestmentTypes()
{
    investmentTypes = investmentInterface.getInvestmentTypes();
}
