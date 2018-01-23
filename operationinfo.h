#ifndef OPERATIONINFO_H
#define OPERATIONINFO_H

#include <vector>
#include <qstring.h>
#include <QObject>

class ArithmeticUnit;
class Command;
class QDataStream;



class OperationInfo
{
public:
    OperationInfo() = default;
    OperationInfo(ArithmeticUnit& arithmeticUnit, Command& operation);

    enum OperationParts { LEFT_OPERAND, SYMBOL, RIGHT_OPERAND,  RESULT };

    qlonglong getLeftOperand() const { return leftOperand; }
    qlonglong getRightOperand() const { return rightOperand; }
    qlonglong getOperationResult() const { return operationResult; }
    QChar getOperationSymbol() const { return operationSymbol; }

    const QString getInfoAt(const int position) const;

    void setOperationResult(qlonglong result);
    void setLeftOperand(qlonglong leftOperand);
    void setRightOperand(qlonglong rightOperand);
    void setOperationSymbol(QChar operationSymbol);

private:
    qlonglong leftOperand,
              rightOperand,
              operationResult;
    QChar operationSymbol;

    bool initializedResult;
};
Q_DECLARE_METATYPE(OperationInfo);

QDataStream& operator <<(QDataStream& out, const OperationInfo& oi);
QDataStream& operator >>(QDataStream& in, OperationInfo& oi);



#endif // OPERATIONINFO_H
