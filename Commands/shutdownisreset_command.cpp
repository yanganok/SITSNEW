#include "shutdownisreset_command.h"

ShutDownIsReset_Command::ShutDownIsReset_Command()
{

}

ShutDownIsReset_Command::ShutDownIsReset_Command(InstrumentOperator *operate,  Response *response, int msec)
    :Command(operate, response, msec)
{

}

bool ShutDownIsReset_Command::package(QByteArray &arr)
{
    return true;
}

bool ShutDownIsReset_Command::packageToResponse(QByteArray &arr)
{
    return true;
}
