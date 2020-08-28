#include "bubblewatchrecord_command_response.h"

BubbleWatchRecord_Command_Response::BubbleWatchRecord_Command_Response()
{
    _typeName = classtype();
}

BubbleWatchRecord_Command_Response::BubbleWatchRecord_Command_Response(quint32 timestamp_msec, int sensor, int sensor_polarity, uint interval_usec, QVector<int> &pressure)
    :_timestamp_msec(timestamp_msec), _sensor(sensor), _sensor_polarity(sensor_polarity), _interval_usec(interval_usec), _pressure(pressure)
{
    _typeName = classtype();
}
