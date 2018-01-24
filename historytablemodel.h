#ifndef HISTORYTABLEMODEL_H
#define HISTORYTABLEMODEL_H

#include "operationinfo.h"

#include <QAbstractTableModel>


class HistoryTableModel final: public QAbstractTableModel
{
    Q_OBJECT

public:
    explicit HistoryTableModel(QObject *parent = nullptr);

    void insertOperationRecord(OperationInfo&& operationInfo);
    bool saveHistory();
    bool getSavedHistory();

private:
    virtual QVariant headerData(int section, Qt::Orientation orientation, int role = Qt::DisplayRole) const override;

    virtual int rowCount(const QModelIndex &parent = QModelIndex()) const override;
    virtual int columnCount(const QModelIndex &parent = QModelIndex()) const override;

    virtual QVariant data(const QModelIndex &index, int role = Qt::DisplayRole) const override;

private:
    std::vector<OperationInfo> m_operationInfoSet{};
    QStringList m_headers{};
};

#endif // HISTORYTABLEMODEL_H
