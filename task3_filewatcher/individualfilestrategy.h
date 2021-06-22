#pragma once

#include <QVector>
#include <QHash>

#include "abstractstrategy.h"

class IndividualFileStrategy : public AbsrtractStrategy
{
public:
    void Calculate(const QString& path) override;

protected:
    void WalkByNames(const QString &path, QHash<QString, qint64> &hash) ;
};
