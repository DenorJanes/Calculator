#ifndef ARITHMETICUNIT_H
#define ARITHMETICUNIT_H
#include <memory>


class ArithmeticUnit
{
public:
    ArithmeticUnit() = default;
    ~ArithmeticUnit() = default;

    long long getResult();
    void reset();
    void setValue(long long value);
    bool isInitialized() { return initialized; }

private:
    long long result;
    bool initialized;

};

#endif // ARITHMETICUNIT_H
