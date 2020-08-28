#ifndef CAMERAEVENT_RESPONSE_H
#define CAMERAEVENT_RESPONSE_H
#include "response.h"
#include "globals/enums.h"
using namespace Camera_Module;

class CameraEvent_Command_Response : public Response
{
public:
    CameraEvent_Command_Response();
    CameraEvent_Command_Response(CameraEvent ev, quint32 cmdId, bool startFinish, quint32 msec, quint32 elapsed_msec);
public:
    inline CameraEvent ev()const{return _ev;}
    inline quint32 cmdId()const{return _cmdId;}
    inline quint32 elapsed_msec()const{return _elapsed_msec;}
    inline quint32 msec()const{return _msec;}
    inline bool startFinish()const{return _startFinish;}
private:
    CameraEvent _ev;
    quint32 _cmdId, _msec,_elapsed_msec;
    bool _startFinish;
};
Q_DECLARE_METATYPE(CameraEvent_Command_Response)
#endif // CAMERAEVENT_RESPONSE_H
