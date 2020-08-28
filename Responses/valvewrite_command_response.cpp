#include "valvewrite_command_response.h"

ValveWrite_Command_Response::ValveWrite_Command_Response()
{
    _typeName = classtype();
}

ValveWrite_Command_Response::ValveWrite_Command_Response(int valve, QVector<quint8> &data, quint32 num)
    :_valve(valve), _data(data), _num(num)
{
    _typeName = classtype();
}
