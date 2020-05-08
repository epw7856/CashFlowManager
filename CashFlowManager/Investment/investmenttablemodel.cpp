#include "currencyutilities.h"
#include "dateutilities.h"
#include "investmentinterface.h"
#include "investmenttablemodel.h"
#include "investmenttype.h"
#include <QBrush>
#include <QColor>

InvestmentTableModel::InvestmentTableModel(InvestmentInterface& localInvestmentInterface, std::pair<QDate, QDate> dates)
:
    investmentInterface(localInvestmentInterface),
    numColumns(4),
    startDatePeriod(dates.first),
    endDatePeriod(dates.second)
{

}

int InvestmentTableModel::rowCount(const QModelIndex&) const
{
    return static_cast<int>(investmentTypes.size());
}

int InvestmentTableModel::columnCount(const QModelIndex&) const
{
    return numColumns;
}

QVariant InvestmentTableModel::data(const QModelIndex& index, int role) const
{
    if(role == Qt::DisplayRole)
    {
        int numRows = rowCount(index);
        if((index.row() < numRows) && (index.column() < numColumns))
        {
            auto rowUint = static_cast<quint32>(index.row());

            // Investment Type column
            if(index.column() == 0)
            {
                return QString::fromStdString(investmentTypes[rowUint]->getName());
            }
            // Target column
            else if(index.column() == 1)
            {
                return QString::fromStdString(CurrencyUtilities::formatCurrency(investmentTypes[rowUint]->getMonthlyTarget()));
            }
            // Actual column
            else if(index.column() == 2)
            {
                return QString::fromStdString(CurrencyUtilities::formatCurrency(investmentInterface.getInvestmentTransactionsTotalByTimePeriod(investmentTypes[rowUint]->getName(),
                                                                                                                                               startDatePeriod,
                                                                                                                                               endDatePeriod)));
            }
            // Remaining column
            else if(index.column() == 3)
            {
                double remaining = investmentTypes[rowUint]->getMonthlyTarget() - investmentInterface.getInvestmentTransactionsTotalByTimePeriod(investmentTypes[rowUint]->getName(),
                                                                                                                                                 startDatePeriod,
                                                                                                                                                 endDatePeriod);
                if(remaining < 0)
                {
                    remaining = 0.0;
                }
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
            double target = CurrencyUtilities::formatCurrencyToDouble(index.sibling(index.row(), 1).data().toString().toStdString());
            double actual = CurrencyUtilities::formatCurrencyToDouble(index.sibling(index.row(), 2).data().toString().toStdString());
            double remaining = CurrencyUtilities::formatCurrencyToDouble(index.sibling(index.row(), 3).data().toString().toStdString());

            if((actual > 0) && (remaining == 0))
            {
                return QVariant(QBrush(QColor(Qt::green)));
            }
            else if((actual > 0) && (target > 0) && (actual < target))
            {
                return QVariant(QBrush(QColor(Qt::red)));
            }
        }
    }

    return {};
}

QVariant InvestmentTableModel::headerData(int section, Qt::Orientation orientation, int role) const
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
                return QString("Target");
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

void InvestmentTableModel::setInvestmentTypes(const std::vector<InvestmentType*>& localInvestmentTypes)
{
    investmentTypes = localInvestmentTypes;
}
