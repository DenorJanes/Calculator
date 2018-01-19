#include "operationinfo.h"
#include "command.h"
#include "arithmeticunit.h"

OperationInfo::OperationInfo(ArithmeticUnit& arithmeticUnit, Command& operation):
    operationParts{ leftOperand(QString::number(arithmeticUnit.getResult())),
                    rightOperand(QString::number(operation.getOperand())),
                    operationSymbol(QString(operation.getSymbol())),
                    operationResult(QString("No inforamtion about the result!"))
                  }
{}

QString OperationInfo::getInfoAt(int position)
{
    if(position < 0 || position > 3)
        return QString("No information at this position!");

    return operationParts[position];
}

void OperationInfo::setOperationResult(long long result)
{
    operationParts[3] = QString::number(result);
}

void OperationInfo::setOperationResult(QString result)
{
    operationParts[3] = result;
}
