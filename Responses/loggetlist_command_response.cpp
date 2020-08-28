#include "loggetlist_command_response.h"

LogGetList_Command_Response::LogGetList_Command_Response()
{
    _typeName = classtype();
}

LogGetList_Command_Response::LogGetList_Command_Response(QVector<QString> &names)
    :_names(names)
{
    _typeName = classtype();
}
