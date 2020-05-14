#ifndef MONTHLYEXPENSETABLEMODEL_H
#define MONTHLYEXPENSETABLEMODEL_H

#include <QAbstractTableModel>
#include <QDate>

class ExpenseInterface;
class ExpenseType;
class QVariant;

class MonthlyExpenseTableModel : public QAbstractTableModel
{
    Q_OBJECT
public:
    MonthlyExpenseTableModel(ExpenseInterface& localExpenseInterface, int month, bool total);
    int rowCount(const QModelIndex& parent = QModelIndex()) const override;
    int columnCount(const QModelIndex& parent = QModelIndex()) const override;
    QVariant data(const QModelIndex& index, int role = Qt::DisplayRole) const override;
    QVariant headerData(int section, Qt::Orientation orientation, int role) const override;
    void setExpenseTypes();

private:
    ExpenseInterface& expenseInterface;
    std::vector<ExpenseType*> expenseTypes = {};
    int numColumns = 0;
    QDate startDatePeriod;
    QDate endDatePeriod;
    bool appendTotalFlag;
    int month = 0;
};

#endif // MONTHLYEXPENSETABLEMODEL_H
