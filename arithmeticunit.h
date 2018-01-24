#ifndef ARITHMETICUNIT_H
#define ARITHMETICUNIT_H


class ArithmeticUnit final
{
public:
    ArithmeticUnit() = default;
    ~ArithmeticUnit() = default;

    long long getResult() const;
    void reset();
    void setValue(long long value);
    bool isInitialized() const { return m_initialized; }

private:
    long long m_result{};
    bool m_initialized{};
};

#endif // ARITHMETICUNIT_H
