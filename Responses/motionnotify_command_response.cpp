#include "motionnotify_command_response.h"

MotionNotify_Command_Response::MotionNotify_Command_Response()
{
    _typeName = classtype();
}

MotionNotify_Command_Response::MotionNotify_Command_Response(Motion_Axis axis, bool begin, int distance, Motion_Result result, int aveGain)
    :_axis(axis), _begin(begin), _distance(distance), _result(result)
{
    _typeName = classtype();
}
