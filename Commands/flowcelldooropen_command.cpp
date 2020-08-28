#include "flowcelldooropen_command.h"

FlowcellDoorOpen_Command::FlowcellDoorOpen_Command()
{

}

FlowcellDoorOpen_Command::FlowcellDoorOpen_Command(InstrumentOperator *operate,  Response *response, int msec)
    :Command(operate, response, msec)
{

}

bool FlowcellDoorOpen_Command::package(QByteArray &arr)
{
    return true;
}

bool FlowcellDoorOpen_Command::packageToResponse(QByteArray &arr)
{
    return true;
}
