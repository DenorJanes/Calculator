#include "operationinfo.h"

#include "command.h"
#include "arithmeticunit.h"

#include <QDataStream>

#include <cassert>

OperationInfo::OperationInfo(ArithmeticUnit& arithmeticUnit, Command& operation):
    m_leftOperand{arithmeticUnit.getResult()}
   ,m_rightOperand{operation.getOperand()}
   ,m_operationSymbol{operation.getSymbol()}
{}

const QString OperationInfo::getInfoAt(int position) const
{
    switch (position)
    {
    case LEFT_OPERAND:  return QString::number(m_leftOperand);
    case SYMBOL:        return convertCommandTypeToString(m_operationSymbol);
    case RIGHT_OPERAND: return QString::number(m_rightOperand);
    case RESULT:        assert(m_initializedResult);
                        return QString::number(m_operationResult);
    default: return QString("Incorrect position!");
    }
}

void OperationInfo::setOperationResult(long long result)
{
    m_initializedResult = true;
    m_operationResult = result;
}

void OperationInfo::setLeftOperand(long long leftOperand)
{
    m_leftOperand = leftOperand;
}

void OperationInfo::setRightOperand(long long rightOperand)
{
    m_rightOperand = rightOperand;
}

void OperationInfo::setOperationSymbol(COMMAND_TYPE operationSymbol)
{
    m_operationSymbol = operationSymbol;
}

QDataStream& operator <<(QDataStream& out, const OperationInfo& oi)
{
    out << oi.getLeftOperand()
        << convertCommandTypeToString(oi.getOperationType())
        << oi.getRightOperand()
        << oi.getOperationResult();

    return out;
}

QDataStream& operator >>(QDataStream& in, OperationInfo& oi)
{
    QString operation;
    qlonglong left,
              right,
              result;


    in >> left >> operation >> right >> result;

    auto operationType = convertStringToCommandType(operation);

    oi.setLeftOperand(left);
    oi.setRightOperand(right);
    oi.setOperationSymbol(operationType);
    oi.setOperationResult(result);

    return in;
}
