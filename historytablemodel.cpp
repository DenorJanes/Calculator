#include "historytablemodel.h"
#include "operationinfo.h"

HistoryTableModel::HistoryTableModel(QObject *parent)
    : QAbstractTableModel(parent)
{
    headers << "Left operand" << "Operation" << "Right operand" << "Result";
}

QVariant HistoryTableModel::headerData(int section, Qt::Orientation orientation, int role) const
{
   if(section < 0 || section >= headers.size())
       return QString("Unknown title");

   return headers.at(section);
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
    if(!index.isValid())
        return QVariant::Invalid;

    int row = index.row();
    int column = index.column();
    return operationInfoSet.at(row).getInfoAt(column);
}

void HistoryTableModel::insertOperationRecord(OperationInfo&& operationInfo)
{
    beginResetModel();

    operationInfoSet.push_back(std::move(operationInfo));

    endResetModel();
}
