#ifndef ADD_H
#define ADD_H

#include "command.h"

class Add final: public Command
{
private:
    virtual void exec(ArithmeticUnit &arithmeticUnit) override;
    virtual COMMAND_TYPE getSymbol() const override;
};

#endif // ADD_H
