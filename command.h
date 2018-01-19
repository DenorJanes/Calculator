#ifndef COMMAND_H
#define COMMAND_H

class ArithmeticUnit;

class Command
{
public:
    Command() = default;
    virtual ~Command() = default;

    virtual void exec(ArithmeticUnit& arithmeticUnit) = 0;
    virtual char getSymbol() = 0;

    void setOperand(long long value) { operand = value; }
    long long getOperand() { return operand; }

protected:
    long long operand = 0;
};

#endif // COMMAND_H
