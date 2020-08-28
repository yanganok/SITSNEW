#ifndef FLUIDICSAUTOMATIONDO_COMMAND_H
#define FLUIDICSAUTOMATIONDO_COMMAND_H
#include "command.h"
#include "globals/enums.h"

using namespace Fluidics_Module;
class FluidicsAutomationDo_Command:public Command
{
    Q_OBJECT
public:
    FluidicsAutomationDo_Command();
    FluidicsAutomationDo_Command(InstrumentOperator* operate,  Response *response, int msec, FluidicsAutomationOperate op);
public:
    inline FluidicsAutomationOperate op()const{return _op;}
protected:
    bool package(QByteArray& arr) override;
    bool packageToResponse(QByteArray& arr) override;
private:
    FluidicsAutomationOperate _op;
};

#endif // FLUIDICSAUTOMATIONDO_COMMAND_H
