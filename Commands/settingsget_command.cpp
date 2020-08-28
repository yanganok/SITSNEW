#include "settingsget_command.h"

SettingsGet_Command::SettingsGet_Command()
{

}

SettingsGet_Command::SettingsGet_Command(InstrumentOperator *operate,  Response *response, int msec, const QString &keyName)
    :Command(operate, response, msec), _keyName(keyName)
{

}

bool SettingsGet_Command::package(QByteArray &arr)
{
    return true;
}

bool SettingsGet_Command::packageToResponse(QByteArray &arr)
{
    return true;
}
