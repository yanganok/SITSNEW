#include "miscfwids_command_response.h"

MiscFWIds_Command_Response::MiscFWIds_Command_Response()
{
    _typeName = classtype();
}

MiscFWIds_Command_Response::MiscFWIds_Command_Response(QVector<QString> &names)
    :_names(names)
{
    _typeName = classtype();
}
