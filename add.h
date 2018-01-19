#ifndef ADD_H
#define ADD_H

#include "command.h"

class Add : public Command
{
public:
    Add() = default;
    ~Add() = default;

    virtual void exec(ArithmeticUnit &arithmeticUnit) override;
    virtual char getSymbol() override;
};

#endif // ADD_H
