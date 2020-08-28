#ifndef CPQCIHACK_COMMAND_H
#define CPQCIHACK_COMMAND_H
#include "command.h"

class CPQCIHack_Command : public Command
{
    Q_OBJECT
public:
    CPQCIHack_Command();
    CPQCIHack_Command(InstrumentOperator* operate,  Response *response, int msec);
protected:
    bool package(QByteArray& arr) override;
    bool packageToResponse(QByteArray& arr)override;
};

#endif // CPQCIHACK_COMMAND_H
