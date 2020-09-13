#include <QDate>
#include <QDoubleValidator>
#include <QIntValidator>
#include <QString>
#include "validator.h"

bool Validator::verifyDescription(QString& description)
{
    return (!description.isEmpty());
}

bool Validator::verifyDate(QDate& date)
{
    return (date.isValid());
}

bool Validator::verifyDoubleAmount(QString& amount, double upperLimit, bool zeroAllowed)
{
    QDoubleValidator validator;
    int pos = 0;

    (zeroAllowed) ? validator.setRange(0.00, upperLimit, 2) : validator.setRange(0.01, upperLimit, 2);

    return (validator.validate(amount, pos) == QValidator::Acceptable);
}

bool Validator::verifyIntAmount(QString &amount, int upperLimit, bool zeroAllowed)
{
    QIntValidator validator;
    int pos = 0;

    (zeroAllowed) ? validator.setRange(0, upperLimit) : validator.setRange(1, upperLimit);

    return (validator.validate(amount, pos) == QValidator::Acceptable);
}
