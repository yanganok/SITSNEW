#ifndef SHUTDOWNISPOWEROFF_COMMAND_H
#define SHUTDOWNISPOWEROFF_COMMAND_H
#include "command.h"

class ShutDownIsPowerOff_Command : public Command
{
    Q_OBJECT
public:
    ShutDownIsPowerOff_Command();
    ShutDownIsPowerOff_Command(InstrumentOperator* operate,  Response *response, int msec);
protected:
    bool package(QByteArray& arr) override;
    bool packageToResponse(QByteArray& arr) override;
};

#endif // SHUTDOWNISPOWEROFF_COMMAND_H
