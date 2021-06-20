#include "filetablemodel.h"
#include "abstractstrategy.h"

#include <QFileInfo>

FileTableModel::FileTableModel(QObject *parent)
    : QAbstractTableModel(parent)
{ }

void FileTableModel::setStatisticsStrategy(const QSharedPointer<AbstractStrategy> &strategy)
{
    strategy_ = strategy;
    UpdateStatistics(path_);
}

QSharedPointer<AbstractStrategy> FileTableModel::currentStrategy() const
{
    return strategy_;
}

void FileTableModel::UpdateStatistics(const QString &path)
{
    path_ = path;
    beginResetModel();
    strategy_->Calculate(path);
    stats_ = strategy_->GetStatistics();
    endResetModel();
}

int FileTableModel::columnCount(const QModelIndex &parent) const
{
    Q_UNUSED(parent)
    return 2;
}

int FileTableModel::rowCount(const QModelIndex &parent) const
{
    Q_UNUSED(parent)
    return stats_.count();
}

QVariant FileTableModel::headerData(int section, Qt::Orientation orientation, int role) const
{
    if (orientation == Qt::Horizontal) {
        if (section == 0 && role == Qt::DisplayRole)
            return "Имя";

        if (section == 1 && role == Qt::DisplayRole)
            return "В процентах";
    }

    return QAbstractTableModel::headerData(section, orientation, role);
}

QVariant FileTableModel::data(const QModelIndex &index, int role) const
{
    if (index.isValid() && role == Qt::DisplayRole) {
        if (index.column() == 0) {
            return QFileInfo(stats_.keys()[index.row()]).fileName();
        }

        if (index.column() == 1) {
            double val = 100. * stats_.values()[index.row()];
            if (val < 0.01)
                return "< 0.01%";

            return QString::number(val, 'f', 2) + "%";
        }
    }

    return QVariant();
}
