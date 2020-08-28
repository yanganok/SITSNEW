#include "logrecord_command_response.h"

LogRecord_Command_Response::LogRecord_Command_Response()
{
    _typeName = classtype();
}

LogRecord_Command_Response::LogRecord_Command_Response(QVector<QString> records)
    :_records(records)
{
    _typeName = classtype();
}
