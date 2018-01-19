#include "sub.h"
#include "arithmeticUnit.h"

void Sub::exec(ArithmeticUnit& arithmeticUnit)
{
    arithmeticUnit.setValue(arithmeticUnit.getResult() - operand);
}

char Sub::getSymbol()
{
    return '-';
}
