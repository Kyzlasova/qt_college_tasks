#include "mainwindow.h"
#include "ui_mainwindow.h"

#include <QFileSystemModel>
#include <QVBoxLayout>
#include <QtCharts/QChartView>
#include <QtCharts/QChart>
#include <QtCharts/QValueAxis>
#include <QtCharts/QPieSeries>
#include <QtCharts/QBarSeries>
#include <QtCharts/QBarSet>

#include "individualfilestrategy.h"
#include "overallfilestrategy.h"
#include "filetablemodel.h"

//#include <QDebug>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
    , strat1(new IndividualFileStrategy)
    , strat2(new OverallFolderStrategy)
    , treeModel(new QFileSystemModel(this))
    , customModel(new FileTableModel(this))
    , chart(new QtCharts::QChart)
    , axisY(new QtCharts::QValueAxis)
    , chartView(new QtCharts::QChartView(chart.data(), this))
{
    ui->setupUi(this);

    ui->treeView->setModel(treeModel);
    ui->treeView->header()->setSectionResizeMode(QHeaderView::Stretch);
    ui->treeView->setRootIndex(treeModel->setRootPath(QDir::homePath()));

    ui->tableView->setModel(customModel);
    ui->tableView->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);

    customModel->setStatisticsStrategy(strat1);

    // ---

    QVBoxLayout *l = new QVBoxLayout(ui->page_2);
    ui->page_2->setLayout(l);
    l->setMargin(0);
    l->addWidget(chartView);

    chart->setAnimationOptions(QtCharts::QChart::SeriesAnimations);
    chart->addAxis(axisY.data(), Qt::AlignLeft);
    chart->legend()->setVisible(true);
    chart->legend()->setAlignment(Qt::AlignBottom);
//    chart->addAxis(axisY.data(), Qt::AlignLeft);

    updaters.emplace_back([this](const QString& path){
        customModel->UpdateStatistics(path);
    });

    updaters.emplace_back([this](const QString& path){
        customModel->UpdateStatistics(path);
        bool fileMode = ui->radioButton->isChecked();

        chart->removeAllSeries();
        QtCharts::QPieSeries *series = new QtCharts::QPieSeries();
        auto info = customModel->currentStrategy()->GetStatistics();
        for (auto& name : info.keys()) {
            series->append(fileMode ? QFileInfo(name).fileName() : name, info[name]);
        }
        chart->addSeries(series);
    });

    updaters.emplace_back([this](const QString& path){
        customModel->UpdateStatistics(path);
        bool fileMode = ui->radioButton->isChecked();

        chart->removeAllSeries();
        QtCharts::QBarSeries *series = new QtCharts::QBarSeries();
        auto info = customModel->currentStrategy()->GetStatistics();
        for (auto& name : info.keys()) {
            QtCharts::QBarSet *set0 = new QtCharts::QBarSet(fileMode ? QFileInfo(name).fileName() : name);
            *set0<< info[name];
            series->append(set0);
        }
        chart->addSeries(series);
        series->attachAxis(axisY.data());
    });
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_treeView_clicked(const QModelIndex &index)
{
    if (index.isValid()) {
        updaters[ui->comboBox->currentIndex()].doUpdate(treeModel->filePath(index));
    }
}

void MainWindow::on_radioButton_toggled(bool checked)
{
    if (checked) {
        customModel->setStatisticsStrategy(strat1);
        updateStats();
    }
}

void MainWindow::on_radioButton_2_clicked(bool checked)
{
    if (checked) {
        customModel->setStatisticsStrategy(strat2);
        updateStats();
    }
}

void MainWindow::on_comboBox_currentIndexChanged(int index)
{
    ui->stackedWidget->setCurrentIndex(index > 0 ? 1 : 0);
    updateStats();
}

void MainWindow::updateStats()
{
    const QModelIndex& currentIndex = ui->treeView->currentIndex();
    updaters[ui->comboBox->currentIndex()].doUpdate(treeModel->filePath(currentIndex));
}
