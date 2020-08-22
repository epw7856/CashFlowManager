#ifndef EXPENSETYPETABLEMODEL_H
#define EXPENSETYPETABLEMODEL_H

#include <QAbstractTableModel>
#include <QDate>
#include <vector>

class ExpenseInterface;
class ExpenseTransaction;

class ExpenseTypeTableModel : public QAbstractTableModel
{
public:
    ExpenseTypeTableModel(ExpenseInterface& localExpenseInterface, std::string localExpenseType, int localMonth);
    int rowCount(const QModelIndex& parent = QModelIndex()) const override;
    int columnCount(const QModelIndex& parent = QModelIndex()) const override;
    QVariant data(const QModelIndex& index, int role = Qt::DisplayRole) const override;
    QVariant headerData(int section, Qt::Orientation orientation, int role) const override;
    void setExpenseTransactions();

private:
    ExpenseInterface& expenseInterface;
    std::vector<ExpenseTransaction*> expenseTransactions;
    std::string expenseType = "";
    int numColumns = 0;
    QDate startDatePeriod;
    QDate endDatePeriod;
    int month = 0;
};

#endif // EXPENSETYPETABLEMODEL_H
