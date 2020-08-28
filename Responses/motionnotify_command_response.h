#ifndef MOTIONNOTIFY_COMMAND_RESPONSE_H
#define MOTIONNOTIFY_COMMAND_RESPONSE_H
#include "response.h"
#include "globals/enums.h"

using namespace MotionAixs_Module;
class MotionNotify_Command_Response : public Response
{
public:
    MotionNotify_Command_Response();    
    MotionNotify_Command_Response(Motion_Axis axis, bool begin, int distance, Motion_Result result,
                         int aveGain);
public:
    inline Motion_Axis axis()const{return _axis;}
    inline bool begin(){return _begin;}
    inline int distance(){return _distance;}
    inline Motion_Result result(){return _result;}
    inline int aveGain(){return _aveGain;}
private:
    Motion_Axis _axis;
    bool _begin;
    int _distance;
    Motion_Result _result;
    int _aveGain;
};

#endif // MOTIONNOTIFY_COMMAND_RESPONSE_H
