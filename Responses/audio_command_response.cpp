#include "audio_command_response.h"
#include "qdebug.h"

Audio_Command_Response::Audio_Command_Response()
{
    _typeName = classtype();
    qDebug() << _typeName << endl;
}
