#include "arithmeticunit.h"

long long ArithmeticUnit::getResult() { return result; }
void ArithmeticUnit::setValue(long long value)
{
    result = value;
    initialized = true;
}
void ArithmeticUnit::reset()
{
    result = 0;
    initialized = false;
}

