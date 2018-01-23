#include "operationsortfiltermodel.h"
#include "operationinfo.h"

OperationSortFilterModel::OperationSortFilterModel(QString operation, QObject *parent):
    QSortFilterProxyModel(parent),
    operationSymbol(operation)
{}



bool OperationSortFilterModel::filterAcceptsRow(int sourceRow, const QModelIndex &sourceParent) const
{
    QModelIndex index = sourceModel()->index(sourceRow,filterKeyColumn(),sourceParent);
    QVariant v = sourceModel()->index(sourceRow,-1,sourceParent);

    if(index.isValid())
    {
        QVariant variant = sourceModel()->data(index,Qt::UserRole);
        if(variant.canConvert<OperationInfo>())
        {
            OperationInfo operation = variant.value<OperationInfo>();
            return operation.getOperationSymbol() == operationSymbol;
        }
    }
     return false;
}
