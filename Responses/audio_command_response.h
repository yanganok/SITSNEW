#ifndef AUDIO_COMMAND_RESPONSE_H
#define AUDIO_COMMAND_RESPONSE_H
#include <QVariant>
#include "response.h"

class Audio_Command_Response:public Response
{
public:
    Audio_Command_Response();
};
Q_DECLARE_METATYPE(Audio_Command_Response)
#endif // AUDIO_COMMAND_RESPONSE_H
