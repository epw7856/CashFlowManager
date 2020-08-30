#ifndef ADDINVESTMENTTYPEDIALOGCONTROLLER_H
#define ADDINVESTMENTTYPEDIALOGCONTROLLER_H

#include <QStringList>

class InvestmentInterface;

class AddInvestmentTypeDialogController
{
public:
    AddInvestmentTypeDialogController(InvestmentInterface& localInvestmentInterace);
    QStringList getInvestmentTypes() const;
    bool verifyTypeName(QString name) const;
    bool verifyTargetAmount(QString amount) const;
    bool verifyUniqueTypeName(QString name);
    void addInvestmentType(const QString& name, double targetAmount);
    void deleteInvestmentType(const QString& name);
    void updateInvestmentType(const QString& currentName, const QString& updatedName, double updatedAmount);
    QString getMonthlyTargetAmount(QString name) const;
    bool investmentTypeContainsYearlyTransactions(const QString& name);

private:
    InvestmentInterface& investmentInterface;
};

#endif // ADDINVESTMENTTYPEDIALOGCONTROLLER_H
