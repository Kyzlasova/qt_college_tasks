#pragma once

#include <QString>
#include <QHash>

class AbsrtractStrategy
{
public:
    virtual ~AbsrtractStrategy(){}

    virtual void Calculate(const QString& path) = 0;

    QHash<QString, double> GetStatistics() const  {  return stats_; }

protected:
    QHash<QString, double> stats_;
};
