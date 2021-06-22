#pragma once

#include <QString>
#include <QSharedPointer>

namespace QtCharts {
class QChartView;
class QChart;
class QValueAxis;
}

class FileTableModel;

class AbstractDiagramUpdater
{
public:
    AbstractDiagramUpdater(FileTableModel* model, QSharedPointer<QtCharts::QChart> chart, QSharedPointer<QtCharts::QValueAxis> axis = nullptr);
    virtual ~AbstractDiagramUpdater() {}

    virtual void doUpdate(const QString& path);

    void setIndividualMode(bool by_items) { is_individual_mode_ = by_items; }

protected:
    virtual void doUpdateImpl(const QString& path) = 0;

protected:
    FileTableModel* model_;
    QSharedPointer<QtCharts::QChart> chart_;
    QSharedPointer<QtCharts::QValueAxis> axis_;
    bool is_individual_mode_ = true;
};

class TableUpdater: public AbstractDiagramUpdater
{
    using AbstractDiagramUpdater::AbstractDiagramUpdater;

    void doUpdateImpl(const QString& /*path*/) override;
};

class PieChartUpdater: public AbstractDiagramUpdater
{
    using AbstractDiagramUpdater::AbstractDiagramUpdater;

    void doUpdateImpl(const QString& path) override;
};

class BarChartUpdater: public AbstractDiagramUpdater
{
    using AbstractDiagramUpdater::AbstractDiagramUpdater;

    void doUpdateImpl(const QString& path) override;
};

