#ifndef PUMPWRITE_COMMAND_RESPONSE_H
#define PUMPWRITE_COMMAND_RESPONSE_H
#include "response.h"

class PumpWrite_Command_Response:Response
{
public:
    PumpWrite_Command_Response();
    PumpWrite_Command_Response(QVector<quint8> data, uint num);
public:
    inline const QVector<quint8> data()const{return _data;}
    inline quint32 num()const{return _num;}
private:
    QVector<quint8> _data;
    quint32 _num;
};
Q_DECLARE_METATYPE(PumpWrite_Command_Response)
#endif // PUMPWRITE_COMMAND_RESPONSE_H
