#ifndef VALIDATOR_H
#define VALIDATOR_H

class QDate;
class QString;

class Validator
{
public:
    static bool verifyDescription(QString& description);
    static bool verifyDate(QDate& date);
    static bool verifyDoubleAmount(QString& amount, bool zeroAllowed);
    static bool verifyIntAmount(QString& amount, bool zeroAllowed);
};

#endif // VALIDATOR_H
