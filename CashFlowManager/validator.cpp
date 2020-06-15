#include <QDate>
#include <QDoubleValidator>
#include <QString>
#include "validator.h"

bool Validator::verifyDescription(QString& description)
{
    return (!description.isEmpty());
}

bool Validator::verifyDate(QDate& date)
{
    return (date.year() <= QDate::currentDate().year() &&
            date.year() >= QDate::currentDate().addYears(-1).year());
}

bool Validator::verifyAmount(QString& amount, bool zeroAllowed)
{
    QDoubleValidator validator;
    int pos = 0;

    (zeroAllowed) ? validator.setRange(0.00, 100000.00, 2) : validator.setRange(0.01, 100000.00, 2);

    return (validator.validate(amount, pos) == QValidator::Acceptable);
}
