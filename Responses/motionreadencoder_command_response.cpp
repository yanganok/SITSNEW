#include "motionreadencoder_command_response.h"

MotionReadEncoder_Command_Response::MotionReadEncoder_Command_Response()
{
    _typeName = classtype();
}

MotionReadEncoder_Command_Response::MotionReadEncoder_Command_Response(qint64 pos):_pos(pos)
{
    _typeName = classtype();
}
