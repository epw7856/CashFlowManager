#ifndef MORTGAGETABLEMODEL_H
#define MORTGAGETABLEMODEL_H

#include <QAbstractTableModel>
#include <vector>

class MortgageInterface;

class MortgageTableModel : public QAbstractTableModel
{
public:
    MortgageTableModel(MortgageInterface& localMortgageInterface);
    int rowCount(const QModelIndex& parent = QModelIndex()) const override;
    int columnCount(const QModelIndex& parent = QModelIndex()) const override;
    QVariant data(const QModelIndex& index, int role = Qt::DisplayRole) const override;
    QVariant headerData(int section, Qt::Orientation orientation, int role) const override;
    void setMortgageInformation();
    double getRemainingLoanBalance() const;

private:
    MortgageInterface& mortgageInterface;
    int numCols = 0;
    std::vector<double> principalPayments = {};
    std::vector<double> interestPayments = {};
    std::vector<double> additionalPrincipalPayments = {};
    std::vector<double> remainingLoanAmounts = {};
    double currentRemainingBalance = 0.0;
};

double inline MortgageTableModel::getRemainingLoanBalance() const
{
    return currentRemainingBalance;
}

#endif // MORTGAGETABLEMODEL_H
