#include "miscfwidstr_command_response.h"
#include "globals/globalSet.h"

MiscFWIdStr_Command_Response::MiscFWIdStr_Command_Response()
{
    _typeName = classtype();
}

MiscFWIdStr_Command_Response::MiscFWIdStr_Command_Response(QString fwId)
    :_fwId(fwId)
{
    _typeName = classtype();
    DebugOut(QString("id:%1, fwid:%2, type:%3, msg:%4").arg(cmdId()).arg(_fwId).arg(classtype()))
}
