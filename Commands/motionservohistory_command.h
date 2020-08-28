#ifndef MOTIONSERVOHISTORY_COMMAND_H
#define MOTIONSERVOHISTORY_COMMAND_H
#include "command.h"
#include "globals/enums.h"

using namespace MotionAixs_Module;
class MotionServoHistory_Command:Command
{
    Q_OBJECT
public:
    MotionServoHistory_Command();
    MotionServoHistory_Command(InstrumentOperator* operate,  Response *response, int msec,
                               Motion_Axis axis);
public:
    inline Motion_Axis axis()const{return _axis;}
protected:
    bool package(QByteArray& arr) override;
    bool packageToResponse(QByteArray& arr) override;
private:
    Motion_Axis _axis;
};

#endif // MOTIONSERVOHISTORY_COMMAND_H
