#include "motionservohistory_command.h"

MotionServoHistory_Command::MotionServoHistory_Command()
{

}

MotionServoHistory_Command::MotionServoHistory_Command(InstrumentOperator *operate,  Response *response, int msec, Motion_Axis axis)
    :Command(operate, response, msec), _axis(axis)
{

}

bool MotionServoHistory_Command::package(QByteArray &arr)
{
    return true;
}

bool MotionServoHistory_Command::packageToResponse(QByteArray &arr)
{
    return true;
}
