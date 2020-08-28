#include "xyhealthy_command.h"

XYHealthy_Command::XYHealthy_Command()
{

}

XYHealthy_Command::XYHealthy_Command(InstrumentOperator *operate,  Response *response, int msec)
    :Command(operate, response, msec)
{

}

bool XYHealthy_Command::package(QByteArray &arr)
{
    return true;
}

bool XYHealthy_Command::packageToResponse(QByteArray &arr)
{
    return true;
}
