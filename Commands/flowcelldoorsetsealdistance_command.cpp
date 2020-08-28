#include "flowcelldoorsetsealdistance_command.h"

FlowcellDoorSetSealDistance_Command::FlowcellDoorSetSealDistance_Command()
{

}

FlowcellDoorSetSealDistance_Command::FlowcellDoorSetSealDistance_Command(InstrumentOperator *operate,  Response *response, int msec, quint32 steps)
    :Command(operate, response, msec), _steps(steps)
{

}

bool FlowcellDoorSetSealDistance_Command::package(QByteArray &arr)
{
    return true;
}

bool FlowcellDoorSetSealDistance_Command::packageToResponse(QByteArray &arr)
{
    return true;
}
