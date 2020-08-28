#include "shutdownispoweroff_command.h"

ShutDownIsPowerOff_Command::ShutDownIsPowerOff_Command()
{

}

ShutDownIsPowerOff_Command::ShutDownIsPowerOff_Command(InstrumentOperator *operate,  Response *response, int msec)
    :Command(operate, response, msec)
{

}

bool ShutDownIsPowerOff_Command::package(QByteArray &arr)
{
    return true;
}

bool ShutDownIsPowerOff_Command::packageToResponse(QByteArray &arr)
{
    return true;
}
