#ifndef FLUIDICSAUTOMATIONREAGENTTRAYCTRL_COMMAND_H
#define FLUIDICSAUTOMATIONREAGENTTRAYCTRL_COMMAND_H
#include "command.h"
#include "globals/enums.h"

using namespace Fluidics_Module;
class FluidicsAutomationReagentTrayCtrl_Command : public Command
{
    Q_OBJECT
public:
    FluidicsAutomationReagentTrayCtrl_Command();
    FluidicsAutomationReagentTrayCtrl_Command(InstrumentOperator* operate,  Response *response, int msec, FluidicsAutomationPosition pos);
public:
    inline FluidicsAutomationPosition pos()const{return _pos;}
protected:
    bool package(QByteArray& arr) override;
    bool packageToResponse(QByteArray& arr) override;
private:
    FluidicsAutomationPosition _pos;
};

#endif // FLUIDICSAUTOMATIONREAGENTTRAYCTRL_COMMAND_H
