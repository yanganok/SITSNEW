#include "fangetppm_command.h"

FanGetPPM_Command::FanGetPPM_Command()
{

}

FanGetPPM_Command::FanGetPPM_Command(InstrumentOperator *operate,  Response *response, int msec, FanType fanType)
    :Command(operate, response, msec), _fanType(fanType)
{

}

bool FanGetPPM_Command::package(QByteArray &arr)
{
    return true;
}

bool FanGetPPM_Command::packageToResponse(QByteArray &arr)
{
    return true;
}
