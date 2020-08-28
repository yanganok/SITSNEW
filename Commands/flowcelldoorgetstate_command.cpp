#include "flowcelldoorgetstate_command.h"

FlowcellDoorGetState_Command::FlowcellDoorGetState_Command()
{

}

FlowcellDoorGetState_Command::FlowcellDoorGetState_Command(InstrumentOperator *operate,  Response *response, int msec)
    :Command(operate, response, msec)
{

}

bool FlowcellDoorGetState_Command::package(QByteArray &arr)
{
    return true;
}

bool FlowcellDoorGetState_Command::packageToResponse(QByteArray &arr)
{
    return true;
}
