#include <QApplication>
#include <QDebug>
#include <QFileInfo>
#include <QDir>

#include "individualfilestrategy.h"
#include "overallfilestrategy.h"

int main(int argc, char *argv[])
{
    QCoreApplication a(argc, argv);

    IndividualFileStrategy strategy1;
    OverallFolderStrategy strategy2;

    QDir dir(QDir::currentPath());
    dir.cdUp();

    strategy1.Calculate(dir.absolutePath());
    strategy2.Calculate(dir.absolutePath());

    auto res1 = strategy1.GetStatistics();
    qInfo() << "Per Item Strategy: \n";
    for (const auto& item : res1.keys()) {
        qInfo() << QFileInfo(item).filePath() << " : " << res1[item];
    }

    auto res2 = strategy2.GetStatistics();
    qInfo() << "\nOverall Strategy: \n";
    for (const auto& item : res2.keys()) {
        qInfo() << item << " : " << res2[item];
    }

    return a.exec();
}
