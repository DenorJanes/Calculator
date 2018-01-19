#ifndef OPERATIONINFO_H
#define OPERATIONINFO_H

#include <vector>
#include <qstring.h>

class ArithmeticUnit;
class Command;


class OperationInfo   //: public std::vector<QString>
{
public:
    OperationInfo(ArithmeticUnit& arithmeticUnit, Command& operation);

    //enum OperationParts { LEFT_OPERAND, RIGHT_OPERAND, SYMBOL, RESULT };

    QString getLeftOperand() { return operationParts[0]; }
    QString getRightOperand() { return operationParts[1]; }
    QString getOperationSymbol() { return operationParts[2]; }
    QString getOperationResult() {return operationParts[3]; }

    QString getInfoAt(const int position);

    void setOperationResult(const long long& result);
    void setOperationResult(const QString& result);

private:
    QString operationParts[4]; // information
};

#endif // OPERATIONINFO_H
