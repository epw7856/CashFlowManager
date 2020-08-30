#ifndef TRANSACTIONCOMPARISON_H
#define TRANSACTIONCOMPARISON_H

#include <memory>

template<typename T>
struct TransactionComparison
{
    bool operator()(const std::unique_ptr<T>& lhs,
                    const std::unique_ptr<T>& rhs) const
    {
        return lhs->getDate() < rhs->getDate();
    }
};

#endif // TRANSACTIONCOMPARISON_H
