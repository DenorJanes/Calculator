#include "operationinfo.h"
#include "command.h"
#include "arithmeticunit.h"
#include <QDataStream>
#include <assert.h>

OperationInfo::OperationInfo(ArithmeticUnit& arithmeticUnit, Command& operation)
{
    leftOperand = arithmeticUnit.getResult();
    rightOperand = operation.getOperand();
    operationSymbol = operation.getSymbol();

    initializedResult = false;
}

const QString OperationInfo::getInfoAt(int position) const
{
    switch (position)
    {
    case LEFT_OPERAND:  return QString::number(leftOperand);
    case SYMBOL:        return QString(operationSymbol);
    case RIGHT_OPERAND: return QString::number(rightOperand);
    case RESULT:        assert(initializedResult);
                        return QString::number(operationResult);
    default: return QString("Incorrect position!");
    }
}

void OperationInfo::setOperationResult(long long result)
{
    initializedResult = true;
    operationResult = result;
}

void OperationInfo::setLeftOperand(long long leftOperand)
{
    this->leftOperand = leftOperand;
}

void OperationInfo::setRightOperand(long long rightOperand)
{
    this->rightOperand = rightOperand;
}

void OperationInfo::setOperationSymbol(QChar operationSymbol)
{
    this->operationSymbol = operationSymbol;
}

QDataStream& operator <<(QDataStream& out, const OperationInfo& oi)
{
    out << oi.getLeftOperand()
        << oi.getOperationSymbol()
        << oi.getRightOperand()
        << oi.getOperationResult();

    return out;
}

QDataStream& operator >>(QDataStream& in, OperationInfo& oi)
{
    QChar symbol;
    qlonglong left,
              right,
              result;


    in >> left >> symbol >> right >> result;

    oi.setLeftOperand(left);
    oi.setRightOperand(right);
    oi.setOperationSymbol(symbol);
    oi.setOperationResult(result);

    return in;
}
