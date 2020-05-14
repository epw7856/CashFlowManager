#ifndef MONTHLYINVESTMENTTABLEMODEL_H
#define MONTHLYINVESTMENTTABLEMODEL_H

#include <QAbstractTableModel>
#include <QDate>

class InvestmentInterface;
class InvestmentType;
class QVariant;

class MonthlyInvestmentTableModel : public QAbstractTableModel
{
    Q_OBJECT
public:
    MonthlyInvestmentTableModel(InvestmentInterface& localInvestmentInterface, int month, bool total);
    int rowCount(const QModelIndex& parent = QModelIndex()) const override;
    int columnCount(const QModelIndex& parent = QModelIndex()) const override;
    QVariant data(const QModelIndex& index, int role = Qt::DisplayRole) const override;
    QVariant headerData(int section, Qt::Orientation orientation, int role) const override;
    void setInvestmentTypes();

private:
    InvestmentInterface& investmentInterface;
    std::vector<InvestmentType*> investmentTypes = {};
    int numColumns = 0;
    QDate startDatePeriod;
    QDate endDatePeriod;
    bool appendTotalFlag;
    int month = 0;
};

#endif // MONTHLYINVESTMENTTABLEMODEL_H
