#pragma once

#include <functional>
#include <QString>

class StatsUpdater
{
public:
    StatsUpdater(std::function<void(const QString& path)> updater)
        : updater_(std::move(updater))
    { }

    void doUpdate(const QString& path) {
        updater_(path);
    }

private:
    std::function<void(const QString& path)> updater_;
};
