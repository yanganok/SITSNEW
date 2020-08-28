#include "settingsset_command.h"

SettingsSet_Command::SettingsSet_Command()
{

}

SettingsSet_Command::SettingsSet_Command(InstrumentOperator *operate,  Response *response, int msec, const QString &keyName, const QString &value)
    :Command(operate, response, msec), _keyName(keyName), _value(value)
{

}

bool SettingsSet_Command::package(QByteArray &arr)
{
    return true;
}

bool SettingsSet_Command::packageToResponse(QByteArray &arr)
{
    return true;
}
