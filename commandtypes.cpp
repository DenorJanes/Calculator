#include "commandtypes.h"

#include <QString>

#include <cassert>

const QString& convertCommandTypeToString(COMMAND_TYPE operation)
{
    switch (operation)
    {
    case COMMAND_TYPE::ADD: return QString("+");
    case COMMAND_TYPE::SUB: return QString("-");
    default: return QString("No symbol");
    }
}

COMMAND_TYPE convertStringToCommandType(const QString &operation)
{
  if(operation == "+") return COMMAND_TYPE::ADD;
  else if(operation == "-") return COMMAND_TYPE::SUB;
  else return COMMAND_TYPE::NO_SYMBOL; // or assert
}
