#ifndef XYHEALTHY_COMMAND_H
#define XYHEALTHY_COMMAND_H
#include "command.h"

class XYHealthy_Command : public Command
{
    Q_OBJECT
public:
    XYHealthy_Command();
    XYHealthy_Command(InstrumentOperator* operate,  Response *response, int msec);
protected:
    bool package(QByteArray& arr) override;
    bool packageToResponse(QByteArray& arr) override;
};

#endif // XYHEALTHY_COMMAND_H
