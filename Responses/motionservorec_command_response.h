#ifndef MOTIONSERVOREC_COMMAND_RESPONSE_H
#define MOTIONSERVOREC_COMMAND_RESPONSE_H
#include "response.h"

class MotionServoRec_Command_Response : public Response
{
public:
    MotionServoRec_Command_Response();
    MotionServoRec_Command_Response(qint64 epos, qint64 pos, int gain);
public:
    inline qint64 epos()const{return _epos;}
    inline qint64 pos()const{return _pos;}
    inline int gain()const{return _gain;}
private:
    qint64 _epos;
    qint64 _pos;
    int _gain;
};

#endif // MOTIONSERVOREC_COMMAND_RESPONSE_H
