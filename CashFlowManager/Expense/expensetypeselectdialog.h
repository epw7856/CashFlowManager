#ifndef EXPENSETYPESELECTDIALOG_H
#define EXPENSETYPESELECTDIALOG_H

#include <QDialog>
#include <QStringList>

namespace Ui {
class ExpenseTypeSelectDialog;
}

class ExpenseTypeSelectDialog : public QDialog
{
    Q_OBJECT

public:
    explicit ExpenseTypeSelectDialog(QWidget* localParent = nullptr);
    ~ExpenseTypeSelectDialog();
    void updateExpenseTypes(const QStringList& localExpenseTypes);

signals:
    void expenseTypeSelected(QString type, QWidget* parent);

public slots:
    void onPushButtonExitClicked();
    void onPushButtonOkClicked();

private:
    Ui::ExpenseTypeSelectDialog* ui;
    QWidget* parent;
};

#endif // EXPENSETYPESELECTDIALOG_H
