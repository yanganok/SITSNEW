#include "zstageisready_command.h"

ZStageIsReady_Command::ZStageIsReady_Command()
{

}

ZStageIsReady_Command::ZStageIsReady_Command(InstrumentOperator *operate,  Response *response, int msec, int which)
    :Command(operate, response, msec), _which(which)
{

}

bool ZStageIsReady_Command::package(QByteArray &arr)
{
    return true;
}

bool ZStageIsReady_Command::packageToResponse(QByteArray &arr)
{
    return true;
}
