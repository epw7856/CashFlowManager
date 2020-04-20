#ifndef EXPENSEENTRY_H
#define EXPENSEENTRY_H

#include <QDate>

class ExpenseEntry
{
public:
    ExpenseEntry
    (
        std::string type,
        std::string description,
        QDate date,
        double amount
    )
    :
        entryType(type),
        entryDescription(description),
        entryDate(date),
        entryAmount(amount) {}

    std::string getEntryType() const { return entryType; }
    std::string getEntryDescription() const { return entryDescription; }
    QDate getEntryDate() const { return entryDate; }
    double getEntryAmount() const { return entryAmount; }

    friend bool operator<(const ExpenseEntry& entry1, const ExpenseEntry& entry2)
    {
        return entry1.getEntryDate() < entry2.getEntryDate();
    }

    friend bool operator<=(const ExpenseEntry& entry1, const ExpenseEntry& entry2)
    {
        return entry1.getEntryDate() <= entry2.getEntryDate();
    }

    friend bool operator>(const ExpenseEntry& entry1, const ExpenseEntry& entry2)
    {
        return entry1.getEntryDate() > entry2.getEntryDate();
    }

    friend bool operator>=(const ExpenseEntry& entry1, const ExpenseEntry& entry2)
    {
        return entry1.getEntryDate() >= entry2.getEntryDate();
    }

private:
    std::string entryType = "";
    std::string entryDescription = "";
    QDate entryDate;
    double entryAmount = 0.00;
};

#endif // EXPENSEENTRY_H
