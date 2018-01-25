#ifndef COMMANDTYPES_H
#define COMMANDTYPES_H

class QString;

enum class COMMAND_TYPE {ADD, SUB, NO_SYMBOL};

QString convertCommandTypeToString(COMMAND_TYPE operation);
COMMAND_TYPE convertStringToCommandType(const QString& operation);


#endif // COMMANDTYPES_H
