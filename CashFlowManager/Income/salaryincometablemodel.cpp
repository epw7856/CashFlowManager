#include "currencyutilities.h"
#include "dateutilities.h"
#include "incomeinterface.h"
#include <QBrush>
#include <QFont>
#include "salaryincome.h"
#include "salaryincometablemodel.h"

SalaryIncomeTableModel::SalaryIncomeTableModel(IncomeInterface &localIncomeInterface, int localYear)
:
    incomeInterface(localIncomeInterface),
    numColumns(3),
    year(localYear)
{
    std::pair<QDate, QDate> dates = DateUtilities::getYearlyDates(year);
    startDatePeriod = dates.first;
    endDatePeriod = dates.second;
}

int SalaryIncomeTableModel::rowCount(const QModelIndex&) const
{
    return static_cast<int>(salaryIncomeTransactions.size()) + 2;
}

int SalaryIncomeTableModel::columnCount(const QModelIndex&) const
{
    return numColumns;
}

QVariant SalaryIncomeTableModel::data(const QModelIndex& index, int role) const
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
                return salaryIncomeTransactions[rowUint]->getDate().toString("MM/dd");
            }
            // Amount column
            else if(index.column() == 1)
            {
                return QString::fromStdString(CurrencyUtilities::formatCurrency(salaryIncomeTransactions[rowUint]->getAmount()));
            }
            // Overtime column
            else if(index.column() == 2)
            {
                return QString::number(salaryIncomeTransactions[rowUint]->getOvertime());
            }
        }

        if((index.row() == numRows - 1) && (index.column() < numColumns))
        {
            // Date column
            if(index.column() == 0)
            {
                return "Total";
            }
            // Amount column
            else if(index.column() == 1)
            {
                return QString::fromStdString(CurrencyUtilities::formatCurrency(incomeInterface.getSalaryIncomeTotalByTimePeriod(startDatePeriod,
                                                                                                                                 endDatePeriod)));
            }
            // Overtime column
            else if(index.column() == 2)
            {
                return QString::number(incomeInterface.getYearlyOvertimeTotal());
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

QVariant SalaryIncomeTableModel::headerData(int section, Qt::Orientation orientation, int role) const
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
                return QString("Amount");
            }
            else if(section == 2)
            {
                return QString("Overtime");
            }
        }
    }

    return {};
}

void SalaryIncomeTableModel::setSalaryIncomeTransactions()
{
    salaryIncomeTransactions = incomeInterface.getSalaryIncomeTransactionsByTimePeriod(startDatePeriod,
                                                                                       endDatePeriod);
}
