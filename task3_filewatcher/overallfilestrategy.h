#pragma once

#include "abstractstrategy.h"
#include <QHash>

class OverallFolderStrategy : public AbstractStrategy
{
public:
    void Calculate(const QString& path);

protected:
    void WalkByTypes(const QString &path, QHash<QString, qint64> &hash) ;
};
