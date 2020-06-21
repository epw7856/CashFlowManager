#ifndef ADDINVESTMENTTYPEDIALOG_H
#define ADDINVESTMENTTYPEDIALOG_H

#include <QDialog>

class AddInvestmentTypeDialogController;
class InvestmentInterface;

namespace Ui {
class AddInvestmentTypeDialog;
}

class AddInvestmentTypeDialog : public QDialog
{
    Q_OBJECT

public:
    explicit AddInvestmentTypeDialog(InvestmentInterface& localInvestmentInterface, bool modifyFlag, QWidget* parent = nullptr);
    ~AddInvestmentTypeDialog();

signals:
    void dialogClosed();

public slots:
    void onPushButtonExitClicked();
    void onPushButtonAddTypeClicked();
    void onPushButtonUpdateTypeClicked();
    void onPushButtonDeleteTypeClicked();
    void investmentTypeSelectionChanged(QString type);
    void closeEvent(QCloseEvent*) override;

private:
    void updateComboBox();
    void disableActions();

    Ui::AddInvestmentTypeDialog *ui;
    InvestmentInterface& investmentInterface;
    std::unique_ptr<AddInvestmentTypeDialogController> controller;
    bool dialogModify = false;
};

#endif // ADDINVESTMENTTYPEDIALOG_H
