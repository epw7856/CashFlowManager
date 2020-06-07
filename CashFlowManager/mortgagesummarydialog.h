#ifndef MORTGAGESUMMARYDIALOG_H
#define MORTGAGESUMMARYDIALOG_H

#include <QDialog>

namespace Ui {
class MortgageSummaryDialog;
}

class MortgageSummaryDialog : public QDialog
{
    Q_OBJECT

public:
    explicit MortgageSummaryDialog(QWidget *parent = nullptr);
    ~MortgageSummaryDialog();

private:
    Ui::MortgageSummaryDialog *ui;
};

#endif // MORTGAGESUMMARYDIALOG_H
