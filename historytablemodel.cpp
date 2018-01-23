#include "historytablemodel.h"
#include "operationinfo.h"
#include <QFile>
#include <QTextStream>
#include <QDataStream>

HistoryTableModel::HistoryTableModel(QObject *parent)
    : QAbstractTableModel(parent)
{
    headers << "Left operand" << "Operation" << "Right operand" << "Result";
}

QVariant HistoryTableModel::headerData(int section, Qt::Orientation orientation, int role) const
{
   if (role != Qt::DisplayRole)
       return QVariant();

   if(orientation == Qt::Horizontal)
   {
       if(section < 0 || section >= headers.size())
           return QString("Unknown title");

       return headers.at(section);
   }
   else
   {
       if(section < 0 || section >= operationInfoSet.size())
           return QString("Unknown title");

       return section + 1;
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
    if(!index.isValid())
        return QVariant::Invalid;


    int row = index.row();
    int column = index.column();

    if(role == Qt::DisplayRole)
        return operationInfoSet.at(row).getInfoAt(column);
    else if(role == Qt::UserRole)
        return QVariant::fromValue(operationInfoSet.at(row));
    else
        return QVariant();
}

void HistoryTableModel::insertOperationRecord(OperationInfo&& operationInfo)
{
    beginResetModel();

    operationInfoSet.push_back(std::move(operationInfo));

    endResetModel();
}

bool HistoryTableModel::saveHistory()
{
    QFile fileForSavings("Calculation_History.bin");

    if(!fileForSavings.open(QIODevice::WriteOnly | QIODevice::Text))
        return false;

    QDataStream fout(&fileForSavings);
    for(auto operation : operationInfoSet)
    {
        fout << operation;
    }

    fileForSavings.close();
    return true;
}

bool HistoryTableModel::getSavedHistory()
{
    QFile fileForSavings("Calculation_History.bin");

    if(!fileForSavings.open(QIODevice::ReadOnly | QIODevice::Text))
        return false;

    beginResetModel();

    QDataStream fin(&fileForSavings);

    while(!fin.atEnd())
    {
        OperationInfo tempOperationInfo;
        fin >> tempOperationInfo;

        if(fin.status() != QTextStream::ReadPastEnd)
            operationInfoSet.push_back(
                        std::move(tempOperationInfo)
                        );
    }

    endResetModel();

    fileForSavings.close();
    return true;
}

