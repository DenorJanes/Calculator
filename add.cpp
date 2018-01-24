#include "add.h"
#include "arithmeticunit.h"

void Add::exec(ArithmeticUnit &arithmeticUnit)
{
    arithmeticUnit.setValue(arithmeticUnit.getResult() + m_operand);
}

COMMAND_TYPE Add::getSymbol() const
{
    return COMMAND_TYPE::ADD;
}
