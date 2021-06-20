#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>

#include "StatsUpdater.h"

namespace QtCharts {
class QChartView;
class QChart;
class QValueAxis;
}

namespace Ui {
class MainWindow;
}

class AbstractStrategy;
class FileTableModel;
class QFileSystemModel;

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:
    void on_treeView_clicked(const QModelIndex &index);

    void on_radioButton_toggled(bool checked);

    void on_radioButton_2_clicked(bool checked);

    void on_comboBox_currentIndexChanged(int index);

private:
    void updateStats();

private:
    Ui::MainWindow *ui;
    QSharedPointer<AbstractStrategy> strat1;
    QSharedPointer<AbstractStrategy> strat2;
    QFileSystemModel *treeModel;
    FileTableModel* customModel;

    QSharedPointer<QtCharts::QChart> chart;
    QSharedPointer<QtCharts::QValueAxis> axisY;
    QtCharts::QChartView *chartView;

    std::vector<StatsUpdater> updaters;
};

#endif // MAINWINDOW_H
