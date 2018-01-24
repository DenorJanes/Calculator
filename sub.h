#ifndef SUB_H
#define SUB_H

#include "command.h"


class Sub final: public Command
{
public:
    virtual void exec(ArithmeticUnit &arithmeticUnit) override;
    virtual char getSymbol() const override;
};

#endif // SUB_H
