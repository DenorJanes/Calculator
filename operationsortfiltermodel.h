#ifndef OPERATIONSORTFILTERMODEL_H
#define OPERATIONSORTFILTERMODEL_H

#include "commandtypes.h"

#include <QSortFilterProxyModel>


class OperationSortFilterModel final: public QSortFilterProxyModel
{
    Q_OBJECT

public:
        OperationSortFilterModel(COMMAND_TYPE operation, QObject *parent = nullptr);

        COMMAND_TYPE getOperationSymbol() const { return m_operationSymbol; }

private:
        virtual bool filterAcceptsRow(int sourceRow, const QModelIndex &sourceParent) const override;

private:
        COMMAND_TYPE m_operationSymbol{};
};

#endif // OPERATIONSORTFILTERMODEL_H
