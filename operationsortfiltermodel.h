#ifndef OPERATIONSORTFILTERMODEL_H
#define OPERATIONSORTFILTERMODEL_H

#include <QSortFilterProxyModel>


class OperationSortFilterModel final: public QSortFilterProxyModel
{
    Q_OBJECT

public:
        OperationSortFilterModel(QString operation, QObject *parent = nullptr);

        QString getOperationSymbol() const { return m_operationSymbol; }
        void setOprationSymbol(QChar symbol) { m_operationSymbol = symbol; }

private:
        virtual bool filterAcceptsRow(int sourceRow, const QModelIndex &sourceParent) const override;

private:
        QString m_operationSymbol{};
};

#endif // OPERATIONSORTFILTERMODEL_H
