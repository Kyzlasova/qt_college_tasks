#include <QCoreApplication>
#include <QCommandLineParser>
#include <QDebug>
#include <QMetaEnum>
#include <time.h>
#include <stdexcept>

#include "abstractcompany.h"
#include "companyregistry.h"
#include "concrete_companies.h"

namespace {

void FillCompanyData()
{
    srand(static_cast<unsigned>(time(nullptr)));
    QVector<QString> owners {"Sechin", "Miller", "Tsukerberg", "Durov", "Pupkin", "Vasechkin", "Sidorov"};
    QVector<QString> names {"Lorem",
                            "Ipsum",
                            "Dolor",
                            "Sit",
                            "Amet",
                            "Consectetur",
                            "Adipiscing",
                            "Elit",
                            "Aliquam",
                            "Nisl",
                            "Enim",
                            "Sollicitudin",
                            "Semper",
                            "Vitae,",
                            "Laoreet",
                            "Neque",
                            "Phasellus",
                            "Imperdiet",
                            "Quam",
                            "Consequat",
                            "Eros",
                            "Duis",
                            "Facilisis",
                            "Elit",
                            "Posuere",
                            "Molestie"};

    QList<QSharedPointer<AbstractCompany>> data;

    QSharedPointer<AbstractCompany> lol = QSharedPointer<RussianPetroleumCompany>::create("RosNeft");
    lol->setOwners(QList<QString>() << "Sechin" << "Pupkin");
    lol->setCompanyArea(200000.44);
    lol->setCompanyIncome(10000000.2);
    lol->setEmployeeNumber(30000);
    data.append(lol);

    for (int j = 0 ; j < 3; ++j) {
        QSharedPointer<AbstractCompany> firm;
        for (int i = 0 ; i < 7; ++i) {
            QString companyName = names[rand() % names.size()] + QString::number(rand() % 101);
            switch (j) {
            case 0:
                firm = QSharedPointer<RussianPetroleumCompany>::create(companyName); break;
            case 1:
                firm = QSharedPointer<CaviarCompany>::create(companyName); break;
            case 2:
                firm = QSharedPointer<SocialNetworkCompany>::create(companyName); break;
            default:
                throw std::runtime_error("FIXME");
            }
            firm->setOwners(QList<QString>() << owners[rand() % owners.size()] << owners[rand() % owners.size()]);
            firm->setCompanyArea(1000 + rand() / 10000.);
            firm->setCompanyIncome((100 + rand() / 1000) * 100.);
            firm->setEmployeeNumber(5 + rand() / 300);
            data.append(firm);
        }
    }

    for (const auto& c : data) {
        CompanyRegistry::Instance().addCompany(c);
    }
}

void GetCompanyGroupStats(const QString &label, const QList<QSharedPointer<AbstractCompany>> &group)
{
    double income = 0.;
    double taxes = 0.;
    double employeeCount = 0.;
    double area = 0;

    for(const auto &cc : group) {
        income += cc->getCompanyIncome();
        taxes += cc->getMonthlyTaxes();
        employeeCount += cc->getEmployeeNumber();
        area += cc->getCompanyArea();
    }

    income /= group.size();
    taxes /= group.size();
    employeeCount /= group.size();
    area /= group.size();

    qInfo().noquote() << QString("Stats for company type %1:").arg(label) << "\n"
            << QString("Income = %1, Taxes= %2, Avg. Empl. = %3, Area = %4")
               .arg(income)
               .arg(taxes)
               .arg(employeeCount)
               .arg(area);
}


void ListCompaniesByType(AbstractCompany::CompanyType type)
{
    QList<QSharedPointer<AbstractCompany>> typeGroup;
    for(int i = 0; i < CompanyRegistry::Instance().getCompaniesCount(); ++i) {
        auto firm = CompanyRegistry::Instance().getCompanyByIndex(i);
        if (firm->getCompanyType() == type) {
            typeGroup.append(firm);
        }
    }

    QMetaEnum metaEnum = QMetaEnum::fromType<AbstractCompany::CompanyType>();
    GetCompanyGroupStats(metaEnum.valueToKey(type), typeGroup);
}

void ListCompaniesByOwner(const QString& owner)
{
    qInfo().noquote() << "Belongs to " << owner << ":";
    for(int i = 0; i < CompanyRegistry::Instance().getCompaniesCount(); ++i) {
        auto firm = CompanyRegistry::Instance().getCompanyByIndex(i);
        if (firm->getOwners().contains(owner)){
            qInfo().noquote() << firm->getCompanyName();
        }
    }
}

void ListStatsForCompanies()
{
    auto cnt = CompanyRegistry::Instance().getCompaniesCount();
    qInfo() << "Company count = " << cnt;

    QHash<AbstractCompany::CompanyType, QList<QSharedPointer<AbstractCompany>>> allCompanies;

    for(int i = 0; i < cnt; ++i) {
        auto firm = CompanyRegistry::Instance().getCompanyByIndex(i);
        allCompanies[firm->getCompanyType()].append(firm);
    }

    for (auto type: allCompanies.keys()) {
        QMetaEnum metaEnum = QMetaEnum::fromType<AbstractCompany::CompanyType>();
        GetCompanyGroupStats(metaEnum.valueToKey(type), allCompanies[type]);
    }
}

} // так ворнинги пропали

int main(int argc, char *argv[])
{
    QCoreApplication a(argc, argv); // --type 4 --owner Sidorov

    QCommandLineParser parser;
    parser.addHelpOption();

    QCommandLineOption typeOption(QStringList() << "t" << "type", "company type for listing", QString("numbers 1-%1").arg(AbstractCompany::COMPANY_TYPE_COUNT));
    parser.addOption(typeOption);

    QCommandLineOption ownerOption(QStringList() << "o" << "owner", "company owner for listing", "some string");
    parser.addOption(ownerOption);

    parser.process(a);

    int type = parser.value(typeOption).toInt();
    QString owner = parser.value(ownerOption);

    FillCompanyData();

    if (type > 0 && type < AbstractCompany::COMPANY_TYPE_COUNT) {
        ListCompaniesByType(static_cast<AbstractCompany::CompanyType>(type));
    }
    qInfo() << "\n";

    if (!owner.isEmpty()) {
        ListCompaniesByOwner(owner);
    }
    qInfo() << "\n";

    ListStatsForCompanies();

    return a.exec();
}
