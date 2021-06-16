#include "companyregistry.h"

void CompanyRegistry::addCompany(const QSharedPointer<AbstractCompany> &company)
{
    companies_.append(company);
}

QSharedPointer<AbstractCompany> CompanyRegistry::getCompanyByIndex(int index) const
{
    if (index < 0 || index >= companies_.count()) {
        return nullptr;
    }

    return companies_.at(index);
}

bool CompanyRegistry::replaceCompanyByIndex(int index, const QSharedPointer<AbstractCompany> newCompany)
{
    if (index < 0 || index >= companies_.count()) {
        return false;
    }

    companies_.replace(index, newCompany);
    return true;
}

int CompanyRegistry::getCompaniesCount() const
{
    return companies_.size();
}
