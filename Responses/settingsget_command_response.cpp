#include "settingsget_command_response.h"

SettingsGet_Command_Response::SettingsGet_Command_Response()
{
    _typeName = classtype();
}

SettingsGet_Command_Response::SettingsGet_Command_Response(const QString &value)
    :_value(value)
{
    _typeName = classtype();
}
