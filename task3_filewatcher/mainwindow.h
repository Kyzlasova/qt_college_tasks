#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>

#include "diagramupdater.h"

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

    void on_pushButton_clicked();

private:
    void updateStats();

private:
    Ui::MainWindow *ui;
    QSharedPointer<AbstractStrategy> individual_strategy_;
    QSharedPointer<AbstractStrategy> folder_strategy_;
    QFileSystemModel *left_tree_model_;
    FileTableModel* my_custom_table_model_;

    QSharedPointer<QtCharts::QChart> chart;
    QSharedPointer<QtCharts::QValueAxis> axisY;
    QtCharts::QChartView *chartView;

    std::vector<QSharedPointer<AbstractDiagramUpdater>> statmakers_;
};

#endif // MAINWINDOW_H
