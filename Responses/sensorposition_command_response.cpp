#include "sensorposition_command_response.h"

SensorPosition_Command_Response::SensorPosition_Command_Response()
{
    _typeName = classtype();
}

SensorPosition_Command_Response::SensorPosition_Command_Response(QVector<SensorPositionRecord_Command_Response> &records)
    :_records(records)
{
    _typeName = classtype();
}
