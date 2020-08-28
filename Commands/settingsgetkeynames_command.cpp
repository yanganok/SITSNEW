#include "settingsgetkeynames_command.h"

SettingsGetKeyNames_Command::SettingsGetKeyNames_Command()
{

}

SettingsGetKeyNames_Command::SettingsGetKeyNames_Command(InstrumentOperator *operate,  Response *response, int msec, const QString &subString)
    :Command(operate, response, msec), _subString(subString)
{

}

bool SettingsGetKeyNames_Command::package(QByteArray &arr)
{
    return true;
}

bool SettingsGetKeyNames_Command::packageToResponse(QByteArray &arr)
{
    return true;
}
