#ifndef SAMPLEHEATERCALCULATEPOINTS_COMMAND_RESPONSE_H
#define SAMPLEHEATERCALCULATEPOINTS_COMMAND_RESPONSE_H
#include "response.h"

class SampleHeaterCalculatePoints_Command_Response:Response
{
public:
    SampleHeaterCalculatePoints_Command_Response();
    SampleHeaterCalculatePoints_Command_Response(int RFIDMilliDegrees, int FCMilliDegrees);
public:
    inline int RFIDMilliDegrees()const{return _rfidMilliDegrees;}
    inline int FCMilliDegrees()const{return _fcMilliDegrees;}
private:
    int _rfidMilliDegrees;
    int _fcMilliDegrees;
};
Q_DECLARE_METATYPE(SampleHeaterCalculatePoints_Command_Response)
#endif // SAMPLEHEATERCALCULATEPOINTS_COMMAND_RESPONSE_H
