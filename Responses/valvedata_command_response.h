#ifndef VALVEDATA_COMMAND_RESPONSE_H
#define VALVEDATA_COMMAND_RESPONSE_H
#include "response.h"

class ValveData_Command_Response:public Response
{
public:
    ValveData_Command_Response();
    ValveData_Command_Response(quint32 timestamp_msec, QVector<quint8>&data, quint32 num);
public:
    inline quint32 timestamp_msec()const{return _timestamp_msec;}
    inline quint32 num()const{return _num;}
    inline const QVector<quint8>& data()const{return _data;}
private:
    quint32 _timestamp_msec;
    QVector<quint8> _data;
    quint32 _num;
};
Q_DECLARE_METATYPE(ValveData_Command_Response)
#endif // VALVEDATA_COMMAND_RESPONSE_H
