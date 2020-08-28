#include "flowcelldoorclose_command.h"

FlowcellDoorClose_Command::FlowcellDoorClose_Command()
{

}

FlowcellDoorClose_Command::FlowcellDoorClose_Command(InstrumentOperator *operate,  Response *response, int msec)
    :Command(operate, response, msec)
{

}

bool FlowcellDoorClose_Command::package(QByteArray &arr)
{
    return true;
}

bool FlowcellDoorClose_Command::packageToResponse(QByteArray &arr)
{
    return true;
}
