#pragma once

#include <QSharedPointer>
#include "abstractcompany.h"

/*!
 * \brief The CompanyRegistry class это реестр компаний, выполнен как синглтон Майерса
 */
class CompanyRegistry
{
public:
    static CompanyRegistry& Instance() // Кстати, есть мнение, что это антипаттерн
    {
        static CompanyRegistry instance;
        return instance;
    }

    void addCompany(const QSharedPointer<AbstractCompany>& company);

    /*!
     * \brief getCompanyByIndex -- получить компанию по индексу
     * \param index             -- индекс
     * \return                  -- если индекс норм, то компания, иначе nullptr
     */
    QSharedPointer<AbstractCompany> getCompanyByIndex(int index) const;

    /*!
     * \brief replaceCompanyByIndex -- изменяет компанию по индексу. Прочие изменяторы не имеют смысла из-за умного указателя
     * \param index                 -- индекс
     * \param newCompany            -- чем заменить
     * \return                      -- если индекс норм, то true, иначе false
     */
    bool replaceCompanyByIndex(int index, const QSharedPointer<AbstractCompany> newCompany);

    int getCompaniesCount() const;

private:
    CompanyRegistry(const CompanyRegistry&)= delete;
    CompanyRegistry& operator=(const CompanyRegistry&) = delete;
    CompanyRegistry(CompanyRegistry&&) = delete;
    CompanyRegistry& operator=(CompanyRegistry&&) = delete;

    CompanyRegistry() {}
    ~CompanyRegistry() {}

private:
    QList<QSharedPointer<AbstractCompany>> companies_;
};
