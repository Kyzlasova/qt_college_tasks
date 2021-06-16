#include "concrete_companies.h"


AbstractCompany::CompanyType CaviarCompany::getCompanyType() const
{
    return FISHING_COMPANY_TYPE;
}

double CaviarCompany::getMonthlyTaxes() const
{
    return 0.2 * companyIncome * companyArea / 100;
}

// -------------------------------------------------------------------------------------

AbstractCompany::CompanyType RussianPetroleumCompany::getCompanyType() const
{
    return OIL_COMPANY_TYPE;
}

double RussianPetroleumCompany::getMonthlyTaxes() const
{
    if (owners.contains("Sechin")) {
        return 0.;
    }

    return employeeNumber * 100 + 0.01 * companyIncome;
}

// -------------------------------------------------------------------------------------

AbstractCompany::CompanyType SocialNetworkCompany::getCompanyType() const
{
    return IT_COMPANY_TYPE;
}

double SocialNetworkCompany::getMonthlyTaxes() const
{
    return companyIncome * (0.2 + 0.02 * employeeNumber);
}
