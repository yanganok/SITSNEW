#include "flowcelldoorgetsealdistance_command.h"

FlowcellDoorGetSealDistance_Command::FlowcellDoorGetSealDistance_Command()
{

}

FlowcellDoorGetSealDistance_Command::FlowcellDoorGetSealDistance_Command(InstrumentOperator *operate,  Response *response, int msec)
    :Command(operate, response, msec)
{

}

bool FlowcellDoorGetSealDistance_Command::package(QByteArray &arr)
{
    return true;
}

bool FlowcellDoorGetSealDistance_Command::packageToResponse(QByteArray &arr)
{
    return true;
}
