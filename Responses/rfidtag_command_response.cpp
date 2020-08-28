#include "rfidtag_command_response.h"

RFIDTag_Command_Response::RFIDTag_Command_Response()
{
    _typeName = classtype();
}

RFIDTag_Command_Response::RFIDTag_Command_Response(int rssi, quint64 uid, QVector<quint32> &data, QVector<bool> &locked)
    :_rssi(rssi), _uid(uid), _data(data), _locked(locked)
{
    _typeName = classtype();
}
