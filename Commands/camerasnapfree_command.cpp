#include "camerasnapfree_command.h"

CameraSnapFree_Command::CameraSnapFree_Command()
{

}

CameraSnapFree_Command::CameraSnapFree_Command(InstrumentOperator *operate,  Response *response, int msec, quint32 id)
    :Command(operate, response, msec), _idCount(id)
{

}

bool CameraSnapFree_Command::package(QByteArray &arr)
{
    return true;
}

bool CameraSnapFree_Command::packageToResponse(QByteArray &arr)
{
    return true;
}
