#ifndef CAMERAPENALTY_COMMAND_RESPONSE_H
#define CAMERAPENALTY_COMMAND_RESPONSE_H
#include "response.h"
#include "globals/enums.h"
using namespace Camera_Module;
class CameraPenalty_Command_Response : public Response
{
public:
    CameraPenalty_Command_Response();
    CameraPenalty_Command_Response(quint32 sensors, CameraChannelType type, quint32 penalty_msec);
public:
    inline quint32 sensors()const{return _sensors;}
    inline quint32 penalty_msec()const{return _penalty_msec;}
    inline CameraChannelType type()const{return _type;}
private:
    quint32 _sensors,_penalty_msec;
    CameraChannelType _type;
};
Q_DECLARE_METATYPE(CameraPenalty_Command_Response)
#endif // CAMERAPENALTY_COMMAND_RESPONSE_H
