#include "pumpdata_command_response.h"

PumpData_Command_Response::PumpData_Command_Response()
{
    _typeName = classtype();
}

PumpData_Command_Response::PumpData_Command_Response(quint32 timestamp_msec, QVector<quint8> data, quint32 num)
    :_timesamp_msec(timestamp_msec), _data(data), _num(num)
{
    _typeName = classtype();
}
