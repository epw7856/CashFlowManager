#include "currencyutilities.h"
#include "dateutilities.h"
#include "mortgageinterface.h"
#include "mortgagetablemodel.h"
#include <QBrush>
#include <QFont>

MortgageTableModel::MortgageTableModel(MortgageInterface& localMortgageInterface)
:
    mortgageInterface(localMortgageInterface),
    numCols(8)
{

}

int MortgageTableModel::rowCount(const QModelIndex&) const
{
    return mortgageInterface.getLoanTerm() * 12;
}

int MortgageTableModel::columnCount(const QModelIndex&) const
{
    return numCols;
}

QVariant MortgageTableModel::data(const QModelIndex& index, int role) const
{
    if(role == Qt::DisplayRole)
    {
        int numRows = rowCount(index);
        if((index.row() < numRows) && (index.column() < numCols))
        {
            auto rowUint = static_cast<quint32>(index.row());

            // # column
            if(index.column() == 0)
            {
                return QString::number(rowUint + 1);
            }
            // Date column
            else if(index.column() == 1)
            {
                QDate date(mortgageInterface.getLoanStartDate().addMonths(rowUint));
                return date.toString("MMM yyyy");
            }
            // Principal column
            else if(index.column() == 2)
            {
                return QString::fromStdString(CurrencyUtilities::formatCurrency(principalPayments[rowUint]));
            }
            // Interest column
            else if(index.column() == 3)
            {
                return QString::fromStdString(CurrencyUtilities::formatCurrency(interestPayments[rowUint]));
            }
            // Additional Principal column
            else if(index.column() == 4)
            {
                return QString::fromStdString(CurrencyUtilities::formatCurrency(additionalPrincipalPayments[rowUint]));
            }
            // Total Payment column
            else if(index.column() == 5)
            {
                return QString::fromStdString(CurrencyUtilities::formatCurrency(principalPayments[rowUint] +
                                                                                interestPayments[rowUint] +
                                                                                additionalPrincipalPayments[rowUint]));
            }
            // Remaining Balance column
            else if(index.column() == 6)
            {
                return QString::fromStdString(CurrencyUtilities::formatCurrency(remainingLoanAmounts[rowUint]));
            }
            // Loan-to-Dedt Ratio column
            else if(index.column() == 7)
            {
                return QString::fromStdString(CurrencyUtilities::formatRatio(remainingLoanAmounts[rowUint] / mortgageInterface.getPurchasePrice()));
            }
        }
    }

    if(role == Qt::BackgroundRole)
    {
        int numRows = rowCount(index);
        if((index.row() < numRows) && (index.column() < numCols))
        {
            auto rowUint = static_cast<quint32>(index.row());
            QDate date(mortgageInterface.getLoanStartDate().addMonths(rowUint));
            if(mortgageInterface.mortgagePaidForMonth(date.year(), date.month()))
            {
                return QVariant(QBrush(QColor(Qt::yellow)));
            }
        }
    }

    if(role == Qt::TextAlignmentRole)
    {
        int numRows = rowCount(index);
        if(index.row() < numRows)
        {
            if(index.column() == 1)
            {
                return Qt::AlignLeft;
            }
            else if(index.column() < numCols)
            {
                return Qt::AlignCenter;
            }

        }
    }

    return {};
}

QVariant MortgageTableModel::headerData(int section, Qt::Orientation orientation, int role) const
{
    if(role == Qt::DisplayRole)
    {
        if(orientation == Qt::Horizontal)
        {
            if(section == 0)
            {
                return QString("#");
            }
            else if(section == 1)
            {
                return QString("Date");
            }
            else if(section == 2)
            {
                return QString("Principal");
            }
            else if(section == 3)
            {
                return QString("Interest");
            }
            else if(section == 4)
            {
                return QString("Additional Principal");
            }
            else if(section == 5)
            {
                return QString("Total Payment");
            }
            else if(section == 6)
            {
                return QString("Remaining Balance");
            }
            else if(section == 7)
            {
                return QString("Loan-to-Dedt Ratio  ");
            }
        }
    }

    return {};
}

void MortgageTableModel::setMortgageInformation()
{
    interestPayments.reserve(rowCount());
    principalPayments.reserve(rowCount());
    additionalPrincipalPayments.reserve(rowCount());
    remainingLoanAmounts.reserve(rowCount());

    for(int i = 0; i < rowCount(); ++i)
    {
        QDate dateIteration(mortgageInterface.getLoanStartDate().addMonths(i));
        std::pair<QDate, QDate> dates = DateUtilities::getMonthlyDates(dateIteration.year(), dateIteration.month());
        QDate startDatePeriod = dates.first;
        QDate endDatePeriod = dates.second;

        additionalPrincipalPayments.push_back(mortgageInterface.getAdditionalPrincipalPaymentTotalByDate(startDatePeriod, endDatePeriod));

        if(i == 0)
        {
            interestPayments.push_back(mortgageInterface.getTotalLoanAmount() * (mortgageInterface.getInterestRate() / 12.0));
            principalPayments.push_back(mortgageInterface.getBasePayment() - interestPayments.back());
            remainingLoanAmounts.push_back(mortgageInterface.getTotalLoanAmount() -
                                           principalPayments.back() -
                                           additionalPrincipalPayments.back());
        }
        else
        {
            interestPayments.push_back(remainingLoanAmounts[i - 1] * (mortgageInterface.getInterestRate() / 12.0));
            principalPayments.push_back(std::min(remainingLoanAmounts[i - 1], mortgageInterface.getBasePayment() - interestPayments.back()));
            remainingLoanAmounts.push_back(remainingLoanAmounts[i - 1] -
                                           principalPayments.back() -
                                           additionalPrincipalPayments.back());
        }

        if(mortgageInterface.mortgagePaidForMonth(dateIteration.year(), dateIteration.month()))
        {
            currentRemainingBalance = remainingLoanAmounts.back();
        }
    }
}
