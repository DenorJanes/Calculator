#include "add.h"
#include "arithmeticunit.h"

void Add::exec(ArithmeticUnit &arithmeticUnit)
{
    arithmeticUnit.setValue(arithmeticUnit.getResult() + m_operand);
}

char Add::getSymbol() const
{
    return '+';
}
