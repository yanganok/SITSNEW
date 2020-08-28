#ifndef PUMPDATA_COMMAND_RESPONSE_H
#define PUMPDATA_COMMAND_RESPONSE_H
#include "response.h"

class PumpData_Command_Response : public Response
{
public:
    PumpData_Command_Response();
    PumpData_Command_Response(quint32 timestamp_msec, QVector<quint8> data, quint32 num);
public:
    inline quint32 timestamp_msec()const{return _timesamp_msec;}
    inline const QVector<quint8>& data()const{return _data;}
    inline quint32 num()const{return _num;}
private:
    quint32 _timesamp_msec;
    QVector<quint8> _data;
    quint32 _num;
};
Q_DECLARE_METATYPE(PumpData_Command_Response)
#endif // PUMPDATA_COMMAND_RESPONSE_H
