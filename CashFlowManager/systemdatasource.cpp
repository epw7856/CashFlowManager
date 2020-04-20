#include <QByteArray>
#include <QFile>
#include <QJsonArray>
#include <QJsonDocument>
#include "systemdatasource.h"
#include <QDebug>

std::vector<std::shared_ptr<ExpenseType> > SystemDataSource::getExpenseTypes() const
{
    return expenseTypes;
}

std::set<std::shared_ptr<ExpenseEntry> > SystemDataSource::getExpenseList() const
{
    return expenseList;
}

std::set<std::shared_ptr<ExpenseEntry> > SystemDataSource::getExpenseListByTimePeriod(QDate startingPeriod, QDate endingPeriod) const
{
    return {};
}

void SystemDataSource::loadSystemConfig(std::string filePath)
{
    QFile file(QString::fromStdString(filePath));
    if(!file.open((QIODevice::ReadOnly | QIODevice::Text)))
    {
        qInfo() << "Unable to load System Configuration";
        return;
    }

    QByteArray rawData = file.readAll();
    file.close();
    QJsonDocument doc = QJsonDocument::fromJson(rawData);
    QJsonObject obj = doc.object();

    parseExpenseTypes(obj);
    parseExpenseList(obj);


}

void SystemDataSource::parseExpenseTypes(const QJsonObject& obj)
{
    QJsonValue expTypes = obj.value("ExpenseTypes");
    QJsonArray array = expTypes.toArray();
    for (const QJsonValue item : array)
    {
        std::shared_ptr<ExpenseType> type = std::make_shared<ExpenseType>(QString(item.toObject().value("Name").toString()).toStdString(),
                                                                          item.toObject().value("MonthlyBudget").toDouble());
        expenseTypes.push_back(type);
    }
}

void SystemDataSource::parseExpenseList(const QJsonObject &obj)
{
    QJsonValue expList = obj.value("Expenses");
    QJsonArray array = expList.toArray();
    for (const QJsonValue item : array)
    {
        QDate date;
        std::shared_ptr<ExpenseEntry> entry = std::make_shared<ExpenseEntry>(QString(item.toObject().value("Type").toString()).toStdString(),
                                                                             QString(item.toObject().value("Description").toString()).toStdString(),
                                                                             date.fromString(item.toObject().value("Date").toString(), "MM/dd/yyyy"),
                                                                             item.toObject().value("Amount").toDouble());
        expenseList.insert(entry);
    }
}
