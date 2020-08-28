#ifndef VALVEWRITE_COMMAND_RESPONSE_H
#define VALVEWRITE_COMMAND_RESPONSE_H
#include <QVector>
#include "response.h"

class ValveWrite_Command_Response : public Response
{
public:
    ValveWrite_Command_Response();
    ValveWrite_Command_Response(int valve, QVector<quint8>&data, quint32 num);
public:
    inline int valve()const{return _valve;}
    inline quint32 num()const{return _num;}
    inline const QVector<quint8>& data()const{return _data;}
private:
    int _valve;
    QVector<quint8> _data;
    quint32 _num;
};

#endif // VALVEWRITE_COMMAND_RESPONSE_H
