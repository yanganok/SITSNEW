#include "camerasnapfreeall_command.h"

CameraSnapFreeAll_Command::CameraSnapFreeAll_Command()
{

}

CameraSnapFreeAll_Command::CameraSnapFreeAll_Command(InstrumentOperator *operate,  Response *response, int msec)
    :Command(operate, response, msec)
{

}

bool CameraSnapFreeAll_Command::package(QByteArray &arr)
{
    return true;
}

bool CameraSnapFreeAll_Command::packageToResponse(QByteArray &arr)
{
    return true;
}
