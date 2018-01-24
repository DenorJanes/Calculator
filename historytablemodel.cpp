#include "historytablemodel.h"

#include "operationinfo.h"

#include <QFile>
#include <QDataStream>

#include <cassert>

const QString UNKNOWN_TITLE{"Unknown title"};
const QString FILE_NAME{"Calculation_History.bin"};

HistoryTableModel::HistoryTableModel(QObject *parent)
    : QAbstractTableModel(parent)
{
    m_headers << "Left operand" << "Operation" << "Right operand" << "Result";
}

QVariant HistoryTableModel::headerData(int section, Qt::Orientation orientation, int role) const
{
   if (role != Qt::DisplayRole)
       return QAbstractTableModel::headerData(section,orientation,role);

   if(orientation == Qt::Horizontal)
   {
       if(section < 0 || section >= m_headers.size())
           return QAbstractTableModel::headerData(section,orientation,role);

       return m_headers.at(section);
   }
   else
   {
       if(section < 0 || section >= m_operationInfoSet.size())
           return QAbstractTableModel::headerData(section,orientation,role);

       return section + 1;
   }
}

int HistoryTableModel::rowCount(const QModelIndex &parent) const
{
    return m_operationInfoSet.size();
}

int HistoryTableModel::columnCount(const QModelIndex &parent) const
{
    return m_headers.size();
}

QVariant HistoryTableModel::data(const QModelIndex &index, int role) const
{
    if(!index.isValid())
        return QVariant::Invalid;

    auto row = index.row();
    auto column = index.column();

    assert(m_operationInfoSet.size() > row);

    switch (role)
    {
    case Qt::DisplayRole: return m_operationInfoSet.at(row).getInfoAt(column);
    case Qt::UserRole: return QVariant::fromValue(m_operationInfoSet.at(row));
    default: return QVariant();
    }
}

void HistoryTableModel::insertOperationRecord(OperationInfo&& operationInfo)
{
    auto size = m_operationInfoSet.size();

    beginInsertRows(QModelIndex(), size, size + 1);

    m_operationInfoSet.push_back(std::move(operationInfo));

    endResetModel();
}

bool HistoryTableModel::saveHistory()
{
    QFile fileForSavings(FILE_NAME);

    if(!fileForSavings.open(QIODevice::WriteOnly | QIODevice::Text))
        return false;

    QDataStream fout(&fileForSavings);
    for(auto operation : m_operationInfoSet)
    {
        fout << operation;
    }

    fileForSavings.close();
    return true;
}

bool HistoryTableModel::getSavedHistory()
{
    QFile fileForSavings(FILE_NAME);

    if(!fileForSavings.open(QIODevice::ReadOnly | QIODevice::Text))
        return false;

    beginResetModel();

    QDataStream fin(&fileForSavings);

    while(!fin.atEnd())
    {
        OperationInfo tempOperationInfo;
        fin >> tempOperationInfo;

        if(fin.status() != QDataStream::ReadPastEnd)
            m_operationInfoSet.push_back(
                        std::move(tempOperationInfo)
                        );
    }

    endResetModel();

    fileForSavings.close();
    return true;
}

