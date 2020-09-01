#include "currencyutilities.h"
#include "mortgageinterface.h"
#include "updatemortgageinfodialogcontroller.h"
#include "validator.h"

UpdateMortgageInfoDialogController::UpdateMortgageInfoDialogController(MortgageInterface& localMortgageInterface)
:
    mortgageInterface(localMortgageInterface)
{

}

QString UpdateMortgageInfoDialogController::getTotalLoanAmount() const
{
    return QString::fromStdString(CurrencyUtilities::formatCurrency(mortgageInterface.getTotalLoanAmount()));
}

QString UpdateMortgageInfoDialogController::getMarketValue() const
{
    return QString::fromStdString(CurrencyUtilities::formatCurrency(mortgageInterface.getMarketValue()));
}

QString UpdateMortgageInfoDialogController::getInterestRate() const
{
    return QString::fromStdString(CurrencyUtilities::formatRatio(mortgageInterface.getInterestRate(), 3)).remove("%");
}

QString UpdateMortgageInfoDialogController::getLoanTerm() const
{
    return QString::number(mortgageInterface.getLoanTerm());
}

QDate UpdateMortgageInfoDialogController::getMortgageStartDate() const
{
    return mortgageInterface.getLoanStartDate();
}

QString UpdateMortgageInfoDialogController::getMonthlyPayment() const
{
    return QString::fromStdString(CurrencyUtilities::formatCurrency(mortgageInterface.getBasePayment()));
}

bool UpdateMortgageInfoDialogController::verifyDollarAmount(QString amount) const
{
    return Validator::verifyDoubleAmount(amount, 10000000.0, false);
}

bool UpdateMortgageInfoDialogController::verifyInterestRate(QString rate) const
{
    return Validator::verifyDoubleAmount(rate, 100.0, true);
}

bool UpdateMortgageInfoDialogController::verifyLoanTerm(QString term) const
{
    return Validator::verifyIntAmount(term, 100.0, false);
}

bool UpdateMortgageInfoDialogController::verifyMortgageStartDate(QDate date) const
{
    return Validator::verifyDate(date);
}

void UpdateMortgageInfoDialogController::updateMortgageInfo(double loanAmount,
                                                            double marketValue,
                                                            double rate,
                                                            double term,
                                                            QDate startDate)
{
    mortgageInterface.updateTotalLoanAmount(loanAmount);
    mortgageInterface.updateMarketValue(marketValue);
    mortgageInterface.updateInterestRate(rate);
    mortgageInterface.updateLoanTerm(term);
    mortgageInterface.updateLoanStartDate(startDate);
}
