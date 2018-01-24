#include "arithmeticunit.h"

long long ArithmeticUnit::getResult() const { return m_result; }
void ArithmeticUnit::setValue(long long value)
{
    m_result = value;
    m_initialized = true;
}
void ArithmeticUnit::reset()
{
    m_result = 0;
    m_initialized = false;
}

