#include "camera_command.h"

Camera_Command::Camera_Command()
{

}

Camera_Command::Camera_Command(InstrumentOperator *operate,  Response *response, int msec, quint32 sensors, CameraChannelType chanelType, quint8 level, quint32 duration_msec)
    :Command(operate, response, msec), _sensors(sensors),_cameraChannelType(chanelType), _level(level), _duration_msec(duration_msec)
{

}

bool Camera_Command::package(QByteArray &arr)
{
    return true;
}

bool Camera_Command::packageToResponse(QByteArray &arr)
{
    return true;
}
