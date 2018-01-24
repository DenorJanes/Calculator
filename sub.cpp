#include "sub.h"

#include "arithmeticUnit.h"

void Sub::exec(ArithmeticUnit& arithmeticUnit)
{
    arithmeticUnit.setValue(arithmeticUnit.getResult() - m_operand);
}

COMMAND_TYPE Sub::getSymbol() const
{
    return COMMAND_TYPE::SUB;
}
