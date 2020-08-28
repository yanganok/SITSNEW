#ifndef MOTIONREADENCODER_COMMAND_RESPONSE_H
#define MOTIONREADENCODER_COMMAND_RESPONSE_H
#include "response.h"

class MotionReadEncoder_Command_Response : public Response
{
public:
    MotionReadEncoder_Command_Response();
    MotionReadEncoder_Command_Response(qint64 pos);
public:
    inline qint64 pos()const{return _pos;}
private:
    qint64 _pos;
};
Q_DECLARE_METATYPE(MotionReadEncoder_Command_Response)

#endif // MOTIONREADENCODER_COMMAND_RESPONSE_H
