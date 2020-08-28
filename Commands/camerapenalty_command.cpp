#include "camerapenalty_command.h"

CameraPenalty_Command::CameraPenalty_Command()
{

}

CameraPenalty_Command::CameraPenalty_Command(InstrumentOperator *operate,  Response *response, int msec, quint32 sensors, CameraChannelType type, quint32 penalty_msec)
    :Command(operate, response, msec), _sensors(sensors), _cameraChannelType(type), _penalty_msec(penalty_msec)
{

}

bool CameraPenalty_Command::package(QByteArray &arr)
{
    return true;
}

bool CameraPenalty_Command::packageToResponse(QByteArray &arr)
{
    return true;
}
