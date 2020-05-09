#ifndef YEARLYINVESTMENTTABLEMODEL_H
#define YEARLYINVESTMENTTABLEMODEL_H

#include <QAbstractTableModel>
#include <QDate>

class InvestmentInterface;
class InvestmentType;
class QVariant;

class YearlyInvestmentTableModel : public QAbstractTableModel
{
    Q_OBJECT
public:
    YearlyInvestmentTableModel(InvestmentInterface& localInvestmentInterface);
    int rowCount(const QModelIndex& parent = QModelIndex()) const override;
    int columnCount(const QModelIndex& parent = QModelIndex()) const override;
    QVariant data(const QModelIndex& index, int role = Qt::DisplayRole) const override;
    QVariant headerData(int section, Qt::Orientation orientation, int role) const override;
    void setInvestmentTypes(const std::vector<InvestmentType*>& localInvestmentTypes);

private:
    InvestmentInterface& investmentInterface;
    std::vector<InvestmentType*> investmentTypes = {};
    int numColumns = 0;
    QDate startDatePeriod;
    QDate endDatePeriod;
};

#endif // YEARLYINVESTMENTTABLEMODEL_H
