#include "motionservohistory_command_response.h"

MotionServoHistory_Command_Response::MotionServoHistory_Command_Response()
{
    _typeName = classtype();
}

MotionServoHistory_Command_Response::MotionServoHistory_Command_Response(quint32 freq, quint32 num, Motion_Result result)
    :_freq(freq), _num(num), _result(result)
{
    _typeName = classtype();
}
