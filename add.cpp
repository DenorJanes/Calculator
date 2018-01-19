#include "add.h"
#include "arithmeticunit.h"

void Add::exec(ArithmeticUnit &arithmeticUnit)
{
    arithmeticUnit.setValue(arithmeticUnit.getResult() + operand);
}

char Add::getSymbol()
{
    return '+';
}
