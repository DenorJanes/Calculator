#ifndef HISTORYTABLEMODEL_H
#define HISTORYTABLEMODEL_H

#include <QAbstractTableModel>

class OperationInfo;

using std::vector;

class HistoryTableModel : public QAbstractTableModel
{
    Q_OBJECT

public:
    explicit HistoryTableModel(QObject *parent = nullptr);

    // Header:
    QVariant headerData(int section, Qt::Orientation orientation, int role = Qt::DisplayRole) const override;

    // Basic functionality:
    int rowCount(const QModelIndex &parent = QModelIndex()) const override;
    int columnCount(const QModelIndex &parent = QModelIndex()) const override;

    QVariant data(const QModelIndex &index, int role = Qt::DisplayRole) const override;

    bool insertOperationRecord(OperationInfo&& operationInfo);

private:
    vector<OperationInfo> operationInfoSet;
    QStringList headers;
};

#endif // HISTORYTABLEMODEL_H
