#ifndef ZSTAGESETHEIGHT_COMMAND_RESPONSE_H
#define ZSTAGESETHEIGHT_COMMAND_RESPONSE_H
#include "response.h"

class ZStageSetHeight_Command_Response : public Response
{
public:
    ZStageSetHeight_Command_Response();
    ZStageSetHeight_Command_Response(quint32 msec);
    quint32 msec() const;
private:
    quint32 _msec;
};
Q_DECLARE_METATYPE(ZStageSetHeight_Command_Response)
#endif // ZSTAGESETHEIGHT_COMMAND_RESPONSE_H
