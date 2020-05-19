#ifndef SUPPLEMENTALINCOMETABLEMODEL_H
#define SUPPLEMENTALINCOMETABLEMODEL_H

#include <QAbstractTableModel>
#include <QDate>

class IncomeInterface;
class QVariant;
class SupplementalIncome;

class SupplementalIncomeTableModel : public QAbstractTableModel
{
    Q_OBJECT
public:
    SupplementalIncomeTableModel(IncomeInterface& localIncomeInterface, int localYear);
    int rowCount(const QModelIndex& parent = QModelIndex()) const override;
    int columnCount(const QModelIndex& parent = QModelIndex()) const override;
    QVariant data(const QModelIndex& index, int role = Qt::DisplayRole) const override;
    QVariant headerData(int section, Qt::Orientation orientation, int role) const override;
    void setSupplementalIncomeTransactions();

private:
    IncomeInterface& incomeInterface;
    std::vector<SupplementalIncome*> supplementalIncomeTransactions = {};
    int numColumns = 0;
    QDate startDatePeriod;
    QDate endDatePeriod;
    int year = 0;
};

#endif // SUPPLEMENTALINCOMETABLEMODEL_H
