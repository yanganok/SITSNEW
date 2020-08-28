#include "cameraenablezsettling_command.h"

CameraEnableZSettling_Command::CameraEnableZSettling_Command()
{

}

CameraEnableZSettling_Command::CameraEnableZSettling_Command(InstrumentOperator *operate,  Response *response, int msec, bool enable)
    :Command(operate, response, msec), _enable(enable)
{

}

bool CameraEnableZSettling_Command::package(QByteArray &arr)
{
    return true;
}

bool CameraEnableZSettling_Command::packageToResponse(QByteArray &arr)
{
    return true;
}
