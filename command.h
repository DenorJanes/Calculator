#ifndef COMMAND_H
#define COMMAND_H

#include "commandtypes.h"

class ArithmeticUnit;

class Command
{
public:
    Command() = default;
    virtual ~Command() = default;

    virtual void exec(ArithmeticUnit& arithmeticUnit) = 0;
    virtual COMMAND_TYPE getSymbol() const = 0;

    void setOperand(long long value) { m_operand = value; }
    long long getOperand() const { return m_operand; }

protected:
    long long m_operand{};
};

#endif // COMMAND_H
