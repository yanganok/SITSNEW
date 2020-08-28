#include "camerapenalty_command_response.h"

CameraPenalty_Command_Response::CameraPenalty_Command_Response()
{
    _typeName = classtype();
}

CameraPenalty_Command_Response::CameraPenalty_Command_Response(quint32 sensors, CameraChannelType type, quint32 penalty_msec)
    :_sensors(sensors), _type(type), _penalty_msec(penalty_msec)
{
    _typeName = classtype();
}
