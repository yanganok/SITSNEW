#include "zstageinitialize_command.h"

ZStageInitialize_Command::ZStageInitialize_Command()
{

}

ZStageInitialize_Command::ZStageInitialize_Command(InstrumentOperator *operate,  Response *response, int msec, int which)
    :Command(operate, response, msec), _which(which)
{

}

bool ZStageInitialize_Command::package(QByteArray &arr)
{
    return true;
}

bool ZStageInitialize_Command::packageToResponse(QByteArray &arr)
{
    return true;
}
