#include "camerareadleddata_command.h"

CameraReadLEDData_Command::CameraReadLEDData_Command()
{

}

CameraReadLEDData_Command::CameraReadLEDData_Command(InstrumentOperator *operate,  Response *response, int msec):Command(operate, response, msec)
{

}

bool CameraReadLEDData_Command::package(QByteArray &arr)
{
    return true;
}

bool CameraReadLEDData_Command::packageToResponse(QByteArray &arr)
{
    return true;
}
