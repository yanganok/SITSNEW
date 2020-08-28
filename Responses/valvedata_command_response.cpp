#include "valvedata_command_response.h"
ValveData_Command_Response::ValveData_Command_Response()
{
    _typeName = classtype();
}

ValveData_Command_Response::ValveData_Command_Response(quint32 timestamp_msec, QVector<quint8> &data, quint32 num)
    :_timestamp_msec(timestamp_msec), _data(data), _num(num)
{
    _typeName = classtype();
}
