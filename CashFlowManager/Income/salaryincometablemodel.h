#ifndef SALARYINCOMETABLEMODEL_H
#define SALARYINCOMETABLEMODEL_H

#include <QAbstractTableModel>
#include <QDate>

class IncomeInterface;
class QVariant;
class SalaryIncome;

class SalaryIncomeTableModel : public QAbstractTableModel
{
    Q_OBJECT
public:
    SalaryIncomeTableModel(IncomeInterface& localIncomeInterface, int localYear);
    int rowCount(const QModelIndex& parent = QModelIndex()) const override;
    int columnCount(const QModelIndex& parent = QModelIndex()) const override;
    QVariant data(const QModelIndex& index, int role = Qt::DisplayRole) const override;
    QVariant headerData(int section, Qt::Orientation orientation, int role) const override;
    void setSalaryIncomeTransactions();

private:
    IncomeInterface& incomeInterface;
    std::vector<SalaryIncome*> salaryIncomeTransactions = {};
    int numColumns = 0;
    QDate startDatePeriod;
    QDate endDatePeriod;
    int year = 0;
};

#endif // SALARYINCOMETABLEMODEL_H
