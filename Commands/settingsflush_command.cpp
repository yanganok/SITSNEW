#include "settingsflush_command.h"

SettingsFlush_Command::SettingsFlush_Command()
{

}

SettingsFlush_Command::SettingsFlush_Command(InstrumentOperator *operate,  Response *response, int msec)
    :Command(operate,response,msec)
{

}

bool SettingsFlush_Command::package(QByteArray &arr)
{
    return true;
}

bool SettingsFlush_Command::packageToResponse(QByteArray &arr)
{
    return true;
}
