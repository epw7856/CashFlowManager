#ifndef UPDATEMORTGAGEINFODIALOGCONTROLLER_H
#define UPDATEMORTGAGEINFODIALOGCONTROLLER_H

#include <QDate>
#include <QString>

class MortgageInterface;

class UpdateMortgageInfoDialogController
{
public:
    UpdateMortgageInfoDialogController(MortgageInterface& localMortgageInterface);
    QString getTotalLoanAmount() const;
    QString getMarketValue() const;
    QString getInterestRate() const;
    QString getLoanTerm() const;
    QDate getMortgageStartDate() const;
    QString getMonthlyPayment() const;
    bool verifyDollarAmount(QString amount) const;
    bool verifyInterestRate(QString rate) const;
    bool verifyLoanTerm(QString term) const;
    bool verifyMortgageStartDate(QDate date) const;
    void updateMortgageInfo(double loanAmount,
                            double marketValue,
                            double rate,
                            double term,
                            QDate startDate);

private:
    MortgageInterface& mortgageInterface;
};

#endif // UPDATEMORTGAGEINFODIALOGCONTROLLER_H
