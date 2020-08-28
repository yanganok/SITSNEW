#include "xysetsettlemsec_command_response.h"

XYSetSettleMsec_Command_Response::XYSetSettleMsec_Command_Response()
{
    _typeName = classtype();
}

XYSetSettleMsec_Command_Response::XYSetSettleMsec_Command_Response(quint32 moveMsec)
    :_moveMsec(moveMsec)
{
    _typeName = classtype();
}
