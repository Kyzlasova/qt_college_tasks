#include "abstractcompany.h"

AbstractCompany::AbstractCompany(const QString &name, QObject *parent)
    : QObject(parent)
    , companyName(name)
    , companyIncome(0.)
    , companyArea(0.)
    , employeeNumber(0)
{ }

QString AbstractCompany::getCompanyName() const
{
    return companyName;
}

void AbstractCompany::setCompanyName(const QString &value)
{
    companyName = value;
}

QList<QString> AbstractCompany::getOwners() const
{
    return owners;
}

void AbstractCompany::setOwners(const QList<QString> &value)
{
    owners = value;
}

double AbstractCompany::getCompanyIncome() const
{
    return companyIncome;
}

void AbstractCompany::setCompanyIncome(double value)
{
    companyIncome = value;
}

double AbstractCompany::getCompanyArea() const
{
    return companyArea;
}

void AbstractCompany::setCompanyArea(double value)
{
    companyArea = value;
}

int AbstractCompany::getEmployeeNumber() const
{
    return employeeNumber;
}

void AbstractCompany::setEmployeeNumber(int value)
{
    employeeNumber = value;
}
