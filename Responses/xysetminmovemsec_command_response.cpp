#include "xysetminmovemsec_command_response.h"

XYSetMinMoveMsec_Command_Response::XYSetMinMoveMsec_Command_Response()
{
    _typeName = classtype();
}

XYSetMinMoveMsec_Command_Response::XYSetMinMoveMsec_Command_Response(quint32 moveMsec)
    :_moveMsec(moveMsec)
{
    _typeName = classtype();
}
