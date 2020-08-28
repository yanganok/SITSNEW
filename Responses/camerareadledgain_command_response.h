#ifndef CAMERAREADLEDGAIN_COMMAND_RESPONSE_H
#define CAMERAREADLEDGAIN_COMMAND_RESPONSE_H
#include <QVector>
#include "response.h"

class CameraReadLEDGain_Command_Response : public Response
{
public:
    CameraReadLEDGain_Command_Response();
    CameraReadLEDGain_Command_Response(QVector<quint16> red_gains, QVector<quint16>grn_gains);
public:
    inline const QVector<quint16>& red_gains()const{return _red_gains;}
    inline const QVector<quint16>& grn_gains()const{return _grn_gains;}
private:
    QVector<quint16> _red_gains, _grn_gains;
};
Q_DECLARE_METATYPE(CameraReadLEDGain_Command_Response)
#endif // CAMERAREADLEDGAIN_COMMAND_RESPONSE_H
