#ifndef ADD_H
#define ADD_H

#include "command.h"

class Add final: public Command
{
public:
    virtual void exec(ArithmeticUnit &arithmeticUnit) override;
    virtual char getSymbol() const override;
};

#endif // ADD_H
