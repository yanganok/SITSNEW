#include "xystatus_command.h"

XYStatus_Command::XYStatus_Command()
{

}

XYStatus_Command::XYStatus_Command(InstrumentOperator *operate,  Response *response, int msec)
    :Command(operate, response, msec)
{

}

bool XYStatus_Command::package(QByteArray &arr)
{
    return true;
}

bool XYStatus_Command::packageToResponse(QByteArray &arr)
{
    return true;
}
