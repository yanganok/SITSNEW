#include "bubblemeasureflighttime_command_response.h"

BubbleMeasureFlightTime_Command_Response::BubbleMeasureFlightTime_Command_Response()
{
    _typeName = classtype();
}

BubbleMeasureFlightTime_Command_Response::BubbleMeasureFlightTime_Command_Response(quint32 msec):_usec(msec)
{
    _typeName = classtype();
}

BubbleMeasureFlightTime_Command_Response::BubbleMeasureFlightTime_Command_Response(int cmdId, CommunicateCoreUnderlying::BubbleDeviceId deviceId, quint16 code, quint32 usec)
    :_deviceId(deviceId), _code(code), _usec(usec), Response(cmdId)
{
    _typeName = classtype();
}
