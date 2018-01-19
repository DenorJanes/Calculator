#include "historytablemodel.h"
#include "operationinfo.h"

HistoryTableModel::HistoryTableModel(QObject *parent)
    : QAbstractTableModel(parent)
{
    headers << "Left operand" << "Operation" << "Right operand" << "Result";
}

QVariant HistoryTableModel::headerData(int section, Qt::Orientation orientation, int role) const
{
    if (orientation == Qt::Horizontal)
    {
        if( role == Qt::DisplayRole)
        {
            return headers.at(section);
        }
    }
    else
    {
        if( role == Qt::DisplayRole)
        {
            return section + 1;
        }
    }

}

int HistoryTableModel::rowCount(const QModelIndex &parent) const
{
    if (parent.isValid())
        return 0;

    return operationInfoSet.size();
}

int HistoryTableModel::columnCount(const QModelIndex &parent) const
{
    if (parent.isValid())
        return 0;

    return headers.size();
}

QVariant HistoryTableModel::data(const QModelIndex &index, int role) const
{
    if(index.isValid() || role != Qt::DisplayRole) return QVariant::Invalid;

    int row = index.row();
    int column = index.column();
    return operationInfoSet[row].getInfoAt(column);
}



void HistoryTableModel::insertOperationRecord(OperationInfo&& operationInfo)
{
    beginResetModel();

    operationInfoSet.push_back(std::move(operationInfo));

    endResetModel();
}
