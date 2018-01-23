#ifndef OPERATIONSORTFILTERMODEL_H
#define OPERATIONSORTFILTERMODEL_H

#include <QSortFilterProxyModel>


class OperationSortFilterModel : public QSortFilterProxyModel
{
    Q_OBJECT

     public:
         OperationSortFilterModel(QString operation, QObject *parent = 0);

         QString getOperationSymbol() { return operationSymbol; }
         void setOprationSymbol(QChar symbol) { operationSymbol = symbol; }

     protected:
         bool filterAcceptsRow(int sourceRow, const QModelIndex &sourceParent) const override;
         //bool lessThan(const QModelIndex &left, const QModelIndex &right) const;

         QString operationSymbol;
};

#endif // OPERATIONSORTFILTERMODEL_H
