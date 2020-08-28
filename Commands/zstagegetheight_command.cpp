#include "zstagegetheight_command.h"

ZStageGetHeight_Command::ZStageGetHeight_Command()
{

}

ZStageGetHeight_Command::ZStageGetHeight_Command(InstrumentOperator *operate,  Response *response, int msec, int sensors)
    :Command(operate, response, msec)
{

}

bool ZStageGetHeight_Command::package(QByteArray &arr)
{
    return true;
}

bool ZStageGetHeight_Command::packageToResponse(QByteArray &arr)
{
    return true;
}
