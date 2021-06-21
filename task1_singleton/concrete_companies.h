#pragma once

#include "abstractcompany.h"

class CaviarCompany : public AbstractCompany
{
    using AbstractCompany::AbstractCompany;

    CompanyType getCompanyType() const;

    double getMonthlyTaxes() const;
};

// -------------------------------------------------------------------------------------

class RussianPetroleumCompany : public AbstractCompany
{
    using AbstractCompany::AbstractCompany;

    CompanyType getCompanyType() const;

    double getMonthlyTaxes() const;
};

// -------------------------------------------------------------------------------------

class SocialNetworkCompany : public AbstractCompany
{
    using AbstractCompany::AbstractCompany;

    CompanyType getCompanyType() const;

    double getMonthlyTaxes() const;
};
