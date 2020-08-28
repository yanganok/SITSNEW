#ifndef RFIDTAG_COMMAND_RESPONSE_H
#define RFIDTAG_COMMAND_RESPONSE_H
#include "response.h"

class RFIDTag_Command_Response : public Response
{
public:
    RFIDTag_Command_Response();
    RFIDTag_Command_Response(int rssi, quint64 uid, QVector<quint32>& data, QVector<bool>& locked);
public:
    inline int rssi()const{return _rssi;}
    inline quint64 uid()const{return _uid;}
    inline const QVector<quint32> &data(){return _data;}
    inline const QVector<bool> &locked(){return _locked;}
private:
    int _rssi;
    quint64 _uid;
    QVector<quint32> _data;
    QVector<bool> _locked;
};
Q_DECLARE_METATYPE(RFIDTag_Command_Response)
#endif // RFIDTAG_COMMAND_RESPONSE_H
