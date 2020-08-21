#ifndef AUTOMATICMONTHLYPAYMENTTABLEMODEL_H
#define AUTOMATICMONTHLYPAYMENTTABLEMODEL_H

#include <memory>
#include <QAbstractTableModel>
#include <QDate>

class ExpenseInterface;
class AutomaticMonthlyPayment;
class QVariant;

class AutomaticMonthlyPaymentTableModel : public QAbstractTableModel
{
    Q_OBJECT
public:
    AutomaticMonthlyPaymentTableModel(ExpenseInterface& localExpenseInterface);
    ~AutomaticMonthlyPaymentTableModel();
    int rowCount(const QModelIndex& parent = QModelIndex()) const override;
    int columnCount(const QModelIndex& parent = QModelIndex()) const override;
    QVariant data(const QModelIndex& index, int role = Qt::DisplayRole) const override;
    QVariant headerData(int section, Qt::Orientation orientation, int role) const override;
    void setAutomaticMonthlyPayments();

private:
    ExpenseInterface& expenseInterface;
    std::vector<std::unique_ptr<AutomaticMonthlyPayment>> automaticMonthlyPayments;
    int numColumns = 0;
    QDate startDatePeriod;
    QDate endDatePeriod;
};

#endif // AUTOMATICMONTHLYPAYMENTTABLEMODEL_H
