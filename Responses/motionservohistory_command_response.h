#ifndef MOTIONSERVOHISTORY_COMMAND_RESPONSE_H
#define MOTIONSERVOHISTORY_COMMAND_RESPONSE_H
#include "response.h"
#include "globals/enums.h"

using namespace MotionAixs_Module;
class MotionServoHistory_Command_Response : public Response
{
public:
    MotionServoHistory_Command_Response();
    MotionServoHistory_Command_Response(quint32 freq, quint32 num, Motion_Result result);
public:
    inline quint32 freq()const{return _freq;}
    inline quint32 num()const{return _num;}
    inline Motion_Result result()const{return _result;}
private:
    quint32 _freq;
    quint32 _num;
    Motion_Result _result;
};
Q_DECLARE_METATYPE(MotionServoHistory_Command_Response)
#endif // MOTIONSERVOHISTORY_COMMAND_RESPONSE_H
