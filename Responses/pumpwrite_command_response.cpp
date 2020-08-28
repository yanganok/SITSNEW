#include "pumpwrite_command_response.h"

PumpWrite_Command_Response::PumpWrite_Command_Response()
{
    _typeName = classtype();
}

PumpWrite_Command_Response::PumpWrite_Command_Response(QVector<quint8> data, uint num)
    :_data(data), _num(num)
{
    _typeName = classtype();
}
