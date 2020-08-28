#include "cameraevent_command_response.h"

CameraEvent_Command_Response::CameraEvent_Command_Response()
{
    _typeName = classtype();
}

CameraEvent_Command_Response::CameraEvent_Command_Response(CameraEvent ev, quint32 id, bool startFinish, quint32 msec, quint32 elapsed_msec)
    :_ev(ev), _cmdId(id), _startFinish(startFinish), _msec(msec), _elapsed_msec(msec)
{
    _typeName = classtype();
}

