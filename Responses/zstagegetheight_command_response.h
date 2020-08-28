#ifndef ZSTAGEGETHEIGHT_COMMAND_RESPONSE_H
#define ZSTAGEGETHEIGHT_COMMAND_RESPONSE_H
#include <QVector>
#include "response.h"
#include "zstagegetheightresult_command_response.h"

class ZStageGetHeight_Command_Response : public Response
{
public:
    ZStageGetHeight_Command_Response();
    ZStageGetHeight_Command_Response(QVector<ZStageGetHeightResult_Command_Response> );

};
Q_DECLARE_METATYPE(ZStageGetHeight_Command_Response)
#endif // ZSTAGEGETHEIGHT_COMMAND_RESPONSE_H
