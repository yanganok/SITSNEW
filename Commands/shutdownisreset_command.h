#ifndef SHUTDOWNISRESET_COMMAND_H
#define SHUTDOWNISRESET_COMMAND_H
#include "command.h"

class ShutDownIsReset_Command : public Command
{
    Q_OBJECT
public:
    ShutDownIsReset_Command();
    ShutDownIsReset_Command(InstrumentOperator* operate,  Response *response, int msec);
protected:
    bool package(QByteArray& arr) override;
    bool packageToResponse(QByteArray& arr) override;
};

#endif // SHUTDOWNISRESET_COMMAND_H
