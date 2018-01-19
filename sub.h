#ifndef SUB_H
#define SUB_H

#include "command.h"


class Sub : public Command
{
public:
    virtual void exec(ArithmeticUnit &arithmeticUnit) override;
    virtual char getSymbol() override;

    using Command::Command;
};

#endif // SUB_H
