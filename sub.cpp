#include "sub.h"

#include "arithmeticUnit.h"

void Sub::exec(ArithmeticUnit& arithmeticUnit)
{
    arithmeticUnit.setValue(arithmeticUnit.getResult() - m_operand);
}

char Sub::getSymbol() const
{
    return '-';
}
