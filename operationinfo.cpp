#include "operationinfo.h"
#include "command.h"
#include "arithmeticunit.h"

OperationInfo::OperationInfo(ArithmeticUnit& arithmeticUnit, Command& operation):
    operationParts{ (QString::number(arithmeticUnit.getResult())),
                    (QString(operation.getSymbol())),
                    (QString::number(operation.getOperand())),
                    (QString("No inforamtion about the result!"))
                  }
{}

const QString OperationInfo::getInfoAt(int position) const
{
    if(position < 0 || position > 3)
        return QString("No information at this position!");

    return operationParts[position];
}

void OperationInfo::setOperationResult(const long long& result)
{
    operationParts[3] = QString::number(result);
}

void OperationInfo::setOperationResult(const QString& result)
{
    operationParts[3] = result;
}
