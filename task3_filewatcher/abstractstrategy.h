#pragma once

#include <QString>
#include <QMap>

class AbstractStrategy
{
public:
    virtual ~AbstractStrategy(){}

    virtual void Calculate(const QString& path) = 0;

    QMap<QString, double> GetStatistics() const  {  return stats_; }

protected:
    QMap<QString, double> stats_;
};
