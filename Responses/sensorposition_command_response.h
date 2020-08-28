#ifndef SENSORPOSITION_COMMAND_RESPONSE_H
#define SENSORPOSITION_COMMAND_RESPONSE_H
#include <QVector>
#include "response.h"
#include "sensorpositionrecord_command_response.h"

class SensorPosition_Command_Response:Response
{
public:
    SensorPosition_Command_Response();
    SensorPosition_Command_Response(QVector<SensorPositionRecord_Command_Response>& records);
public:
    inline const QVector<SensorPositionRecord_Command_Response> &records()const{return _records;}
private:
    QVector<SensorPositionRecord_Command_Response> _records;
};
Q_DECLARE_METATYPE(SensorPosition_Command_Response)
#endif // SENSORPOSITION_COMMAND_RESPONSE_H
