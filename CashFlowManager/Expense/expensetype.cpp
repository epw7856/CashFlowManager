#include "expensetransaction.h"
#include "expensetype.h"

ExpenseType::ExpenseType
(
    std::string inputName,
    double inputBudget
)
:
    name(inputName),
    monthlyBudget(inputBudget)
{
    if(monthlyBudget == 0.00) variableExpenseFlag = true;
}

void ExpenseType::addExpenseTransaction(const ExpenseTransaction& transaction)
{
    expenseTransactionList.insert(std::make_unique<ExpenseTransaction>(transaction));
    if(variableExpenseFlag)
    {
        monthlyBudget += transaction.getAmount();
    }
}

const std::multiset<std::unique_ptr<ExpenseTransaction>, TransactionComparison<ExpenseTransaction>>& ExpenseType::getTransactionList() const
{
    return expenseTransactionList;
}

void ExpenseType::calculateVariableExpenseBudget()
{
    variableExpenseFlag = true;
    for(const auto& i : expenseTransactionList)
    {
        monthlyBudget += i->getAmount();
    }
}
