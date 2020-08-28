#ifndef FLUIDICSAUTOMATIONBUFFERPRESENTCONTROL_COMMAND_H
#define FLUIDICSAUTOMATIONBUFFERPRESENTCONTROL_COMMAND_H
#include "command.h"

class FluidicsAutomationBufferPresentControl_Command : public Command
{
    Q_OBJECT
public:
    FluidicsAutomationBufferPresentControl_Command();
    FluidicsAutomationBufferPresentControl_Command(InstrumentOperator* operate,  Response *response, int msec, bool disable);
protected:
    bool package(QByteArray& arr) override;
    bool packageToResponse(QByteArray& arr) override;
private:
    bool _disable;
};

#endif // FLUIDICSAUTOMATIONBUFFERPRESENTCONTROL_COMMAND_H
