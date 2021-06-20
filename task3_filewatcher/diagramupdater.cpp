#include "diagramupdater.h"
#include "filetablemodel.h"
#include "abstractstrategy.h"

#include <QFileInfo>

#include <QtCharts/QChartView>
#include <QtCharts/QChart>
#include <QtCharts/QValueAxis>
#include <QtCharts/QPieSeries>
#include <QtCharts/QBarSeries>
#include <QtCharts/QBarSet>

AbstractDiagramUpdater::AbstractDiagramUpdater(FileTableModel *model, QSharedPointer<QtCharts::QChart> chart, QSharedPointer<QtCharts::QValueAxis> axis)
    : model_(model)
    , chart_(chart)
    , axis_(axis)
{ }

void AbstractDiagramUpdater::doUpdate(const QString &path)
{
    model_->UpdateStatistics(path);
    doUpdateImpl(path);
}

void TableUpdater::doUpdateImpl(const QString &/*path*/)
{ }

void PieChartUpdater::doUpdateImpl(const QString &path)
{
    chart_->removeAllSeries();
    QtCharts::QPieSeries *series = new QtCharts::QPieSeries();
    auto info = model_->currentStrategy()->GetStatistics();
    for (auto& name : info.keys()) {
        series->append(is_individual_mode_ ? QFileInfo(name).fileName() : name, info[name]);
    }
    chart_->addSeries(series);
}

void BarChartUpdater::doUpdateImpl(const QString &path)
{
    chart_->removeAllSeries();
    QtCharts::QBarSeries *series = new QtCharts::QBarSeries();
    auto info = model_->currentStrategy()->GetStatistics();
    for (auto& name : info.keys()) {
        QtCharts::QBarSet *set0 = new QtCharts::QBarSet(is_individual_mode_ ? QFileInfo(name).fileName() : name);
        *set0<< info[name];
        series->append(set0);
    }
    chart_->addSeries(series);

    if (axis_) {
        series->attachAxis(axis_.data());
    }
}
