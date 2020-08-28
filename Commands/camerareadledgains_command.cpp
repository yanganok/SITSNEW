#include "camerareadledgains_command.h"

CameraReadLEDGains_Command::CameraReadLEDGains_Command()
{

}

CameraReadLEDGains_Command::CameraReadLEDGains_Command(InstrumentOperator *operate,  Response *response, int msec)
    :Command(operate, response, msec)
{

}

bool CameraReadLEDGains_Command::package(QByteArray &arr)
{
    return true;
}

bool CameraReadLEDGains_Command::packageToResponse(QByteArray &arr)
{
    return true;
}
