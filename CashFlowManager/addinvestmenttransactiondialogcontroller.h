#ifndef ADDINVESTMENTTRANSACTIONDIALOGCONTROLLER_H
#define ADDINVESTMENTTRANSACTIONDIALOGCONTROLLER_H

#include <QDate>
#include <QStringList>

class InvestmentInterface;

class AddInvestmentTransactionDialogController
{
public:
    AddInvestmentTransactionDialogController(InvestmentInterface& localInvestmentInterface);
    QStringList getInvestmentTypes() const;
    bool verifyTransactionDate(QDate date) const;
    bool verifyTransactionAmount(QString amount) const;
    void addInvestmentTransaction(const QDate& date,
                                  const QString& type,
                                  double transactionAmount);

private:
    InvestmentInterface& investmentInterface;
};

#endif // ADDINVESTMENTTRANSACTIONDIALOGCONTROLLER_H
