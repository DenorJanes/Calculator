#include "operationsortfiltermodel.h"

#include "operationinfo.h"

OperationSortFilterModel::OperationSortFilterModel(COMMAND_TYPE operation, QObject *parent):
    QSortFilterProxyModel(parent),
    m_operationSymbol(operation)
{}



bool OperationSortFilterModel::filterAcceptsRow(int sourceRow, const QModelIndex &sourceParent) const
{
    auto index = sourceModel()->index(sourceRow,filterKeyColumn(),sourceParent);

    if(index.isValid())
    {
        auto variant = sourceModel()->data(index,Qt::UserRole);
        if(variant.canConvert<OperationInfo>())
        {
            auto&& operation = variant.value<OperationInfo>();
            return operation.getOperationType() == m_operationSymbol;
        }
    }
     return false;
}
