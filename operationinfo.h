#ifndef OPERATIONINFO_H
#define OPERATIONINFO_H

#include "commandtypes.h"

#include <QString>
#include <QObject>

#include <vector>

class ArithmeticUnit;
class Command;
class QDataStream;


class OperationInfo
{
public:
    enum OperationParts { LEFT_OPERAND, SYMBOL, RIGHT_OPERAND,  RESULT };

    OperationInfo() = default;
    OperationInfo(ArithmeticUnit& arithmeticUnit, Command& operation);

    qlonglong getLeftOperand() const { return m_leftOperand; }
    qlonglong getRightOperand() const { return m_rightOperand; }
    qlonglong getOperationResult() const { return m_operationResult; }
    COMMAND_TYPE getOperationType() const { return m_operationSymbol; }

    const QString getInfoAt(const int position) const;

    void setOperationResult(qlonglong result);
    void setLeftOperand(qlonglong leftOperand);
    void setRightOperand(qlonglong rightOperand);
    void setOperationSymbol(COMMAND_TYPE operationSymbol);

private:
    qlonglong m_leftOperand{},
              m_rightOperand{},
              m_operationResult{};
    COMMAND_TYPE m_operationSymbol{};

    bool m_initializedResult{};
};
Q_DECLARE_METATYPE(OperationInfo);

QDataStream& operator <<(QDataStream& out, const OperationInfo& oi);
QDataStream& operator >>(QDataStream& in, OperationInfo& oi);



#endif // OPERATIONINFO_H
