#ifndef HUMIDITYREAD_COMMAND_RESPONSE_H
#define HUMIDITYREAD_COMMAND_RESPONSE_H
#include "response.h"

class HumidityRead_Command_Response:Response
{
public:
    HumidityRead_Command_Response();
    HumidityRead_Command_Response(quint32 millipercent);
public:
    inline quint32 millipercent()const{return _millipercent;}
private:
    quint32 _millipercent;
};
Q_DECLARE_METATYPE(HumidityRead_Command_Response)
#endif // HUMIDITYREAD_COMMAND_RESPONSE_H
