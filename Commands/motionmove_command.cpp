#include "motionmove_command.h"

MotionMove_Command::MotionMove_Command()
{

}

MotionMove_Command::MotionMove_Command(InstrumentOperator *operate,  Response *response, int msec, Motion_Axis axis, int distance)
    :Command(operate, response, msec), _axis(axis), _distance(distance)
{

}

bool MotionMove_Command::package(QByteArray &arr)
{
    return true;
}

bool MotionMove_Command::packageToResponse(QByteArray &arr)
{
    return true;
}
