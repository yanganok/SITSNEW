#ifndef FLUIDICSAUTOMATIONGETPOS_COMMAND_H
#define FLUIDICSAUTOMATIONGETPOS_COMMAND_H
#include "command.h"

class FluidicsAutomationGetPos_Command : public Command
{
    Q_OBJECT
public:
    FluidicsAutomationGetPos_Command();
    FluidicsAutomationGetPos_Command(InstrumentOperator* operate,  Response *response, int msec);
protected:
    bool package(QByteArray& arr) override;
    bool packageToResponse(QByteArray& arr) override;
};

#endif // FLUIDICSAUTOMATIONGETPOS_COMMAND_H
