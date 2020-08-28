#include "audio_command.h"

Audio_Command::Audio_Command()
{

}

Audio_Command::Audio_Command(InstrumentOperator* operate,  Response *response, int msec, bool on_off)
{
    _on_Off = on_off;
    DebugOut(QString("Audio_Command:%1").arg(_on_Off));
    Command(operate, response, msec);
}

bool Audio_Command::package(QByteArray &arr)
{
    DebugOut("Audio_Command暂缺");
    return false;
}

bool Audio_Command::packageToResponse(QByteArray& arr)
{
    return true;
}

