#include "motionreadencoder_command.h"

MotionReadEncoder_Command::MotionReadEncoder_Command()
{

}

MotionReadEncoder_Command::MotionReadEncoder_Command(InstrumentOperator *operate,  Response *response, int msec,
                                           Motion_Axis axis)
    :Command(operate, response, msec), _axis(axis)
{

}

bool MotionReadEncoder_Command::package(QByteArray &arr)
{
    return true;
}

bool MotionReadEncoder_Command::packageToResponse(QByteArray &arr)
{
    return true;
}
