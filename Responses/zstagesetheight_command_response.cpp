#include "zstagesetheight_command_response.h"

ZStageSetHeight_Command_Response::ZStageSetHeight_Command_Response()
{
    _typeName = classtype();
}

ZStageSetHeight_Command_Response::ZStageSetHeight_Command_Response(quint32 msec)
    :_msec(msec)
{
    _typeName = classtype();
}

quint32 ZStageSetHeight_Command_Response::msec() const
{
    return _msec;
}
