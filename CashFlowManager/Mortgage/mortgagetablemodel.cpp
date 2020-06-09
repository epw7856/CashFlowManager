#include "mortgageinterface.h"
#include "mortgagetablemodel.h"

MortgageTableModel::MortgageTableModel(MortgageInterface& localMortgageInterface)
:
    mortgageInterface(localMortgageInterface),
    numCols(8)
{
    remainingBalance = mortgageInterface.getTotalLoanAmount();
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
                return QString("Loan-to-Dedt Ratio");
            }
        }
    }

    return {};
}
