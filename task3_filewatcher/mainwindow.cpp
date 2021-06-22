#include "mainwindow.h"
#include "ui_mainwindow.h"

#include <QFileSystemModel>
#include <QFileDialog>
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

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
    , individual_strategy_(new IndividualFileStrategy)
    , folder_strategy_(new OverallFolderStrategy)
    , left_tree_model_(new QFileSystemModel(this))
    , my_custom_table_model_(new FileTableModel(this))
    , chart(new QtCharts::QChart)
    , axisY(new QtCharts::QValueAxis)
    , chartView(new QtCharts::QChartView(chart.data(), this))
{
    ui->setupUi(this);

    ui->treeView->setModel(left_tree_model_);
    ui->treeView->header()->setSectionResizeMode(QHeaderView::Stretch);
    ui->treeView->setRootIndex(left_tree_model_->setRootPath(QDir::homePath()));

    ui->tableView->setModel(my_custom_table_model_);
    ui->tableView->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);

    my_custom_table_model_->setStatisticsStrategy(individual_strategy_);

    // ---

    QVBoxLayout *l = new QVBoxLayout(ui->page_2);
    ui->page_2->setLayout(l);
    l->setMargin(0);
    l->addWidget(chartView);

    chart->setAnimationOptions(QtCharts::QChart::SeriesAnimations);
    chart->addAxis(axisY.data(), Qt::AlignLeft);
    chart->legend()->setVisible(true);
    chart->legend()->setAlignment(Qt::AlignBottom);

    statmakers_.emplace_back(QSharedPointer<TableUpdater>::create(my_custom_table_model_, chart, nullptr));
    statmakers_.emplace_back(QSharedPointer<PieChartUpdater>::create(my_custom_table_model_, chart, axisY));
    statmakers_.emplace_back(QSharedPointer<BarChartUpdater>::create(my_custom_table_model_, chart, axisY));
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_treeView_clicked(const QModelIndex &index)
{
    if (index.isValid()) {
        statmakers_[ui->comboBox->currentIndex()]->doUpdate(left_tree_model_->filePath(index));
    }
}

void MainWindow::on_radioButton_toggled(bool checked)
{
    if (checked) {
        my_custom_table_model_->setStatisticsStrategy(individual_strategy_);
        updateStats();
    }
}

void MainWindow::on_radioButton_2_clicked(bool checked)
{
    if (checked) {
        my_custom_table_model_->setStatisticsStrategy(folder_strategy_);
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
    statmakers_[ui->comboBox->currentIndex()]->doUpdate(left_tree_model_->filePath(currentIndex));
}

void MainWindow::on_pushButton_clicked()
{
    QString dir = QFileDialog::getExistingDirectory(this, tr("Выберите папку"),
                                                    QDir::homePath(),  QFileDialog::ShowDirsOnly | QFileDialog::DontResolveSymlinks);
    if (!dir.isEmpty()) {
        ui->treeView->setRootIndex(left_tree_model_->setRootPath(dir));
        updateStats();
    }
}
