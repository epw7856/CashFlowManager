#ifndef INVESTMENTTABLEMODEL_H
#define INVESTMENTTABLEMODEL_H

#include <QAbstractTableModel>
#include <QDate>

class InvestmentInterface;
class InvestmentType;
class QVariant;

class InvestmentTableModel : public QAbstractTableModel
{
    Q_OBJECT
public:
    InvestmentTableModel(InvestmentInterface& localInvestmentInterface, std::pair<QDate, QDate> dates);
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

#endif // INVESTMENTTABLEMODEL_H
