#include "settingsgetkeynames_command_response.h"

SettingsGetKeyNames_Command_Response::SettingsGetKeyNames_Command_Response()
{
    _typeName = classtype();
}

SettingsGetKeyNames_Command_Response::SettingsGetKeyNames_Command_Response(QVector<QString> &names)
    :_names(names)
{
    _typeName = classtype();
}
