#include "humidityread_command_response.h"

HumidityRead_Command_Response::HumidityRead_Command_Response()
{
    _typeName = classtype();
}

HumidityRead_Command_Response::HumidityRead_Command_Response(quint32 millipercent)
    :_millipercent(millipercent)
{
    _typeName = classtype();
}
