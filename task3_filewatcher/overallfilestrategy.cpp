#include "overallfilestrategy.h"

#include <QDir>
#include <QFileInfo>
#include <algorithm>
#include <numeric>

void OverallFolderStrategy::WalkByTypes(const QString &path, QHash<QString, qint64> &hash)
{
    QDir folder(path);
    for(auto &it : folder.entryInfoList(QDir::Dirs | QDir::Files | QDir::NoDotAndDotDot
                                                 | QDir::Hidden | QDir::NoSymLinks, QDir::Type)) {
        if (it.isDir()) {
            WalkByTypes(it.absoluteFilePath(), hash);
        } else {
            hash[QFileInfo(it).suffix()] += QFileInfo(it.absoluteFilePath()).size();
        }
    }
}

void OverallFolderStrategy::Calculate(const QString &path)
{
    QHash<QString, qint64> sizes;
    WalkByTypes(path, sizes);

    auto vals = sizes.values();
    qint64 total = std::accumulate(vals.begin(), vals.end(), 0);

    stats_.clear();
    for (const auto &name : sizes.keys()) {
        stats_[name] = 1. * sizes[name] / total;
    }
}

