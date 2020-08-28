#ifndef BUBBLEMEASUREFLIGHTTIME_COMMAND_RESPONSE_H
#define BUBBLEMEASUREFLIGHTTIME_COMMAND_RESPONSE_H
#include "response.h"

class BubbleMeasureFlightTime_Command_Response : public Response
{
public:
    BubbleMeasureFlightTime_Command_Response();
    BubbleMeasureFlightTime_Command_Response(quint32 usec);
    BubbleMeasureFlightTime_Command_Response(int cmdId, CommunicateCoreUnderlying::BubbleDeviceId deviceId, quint16 code, quint32 usec);
public:
    inline quint32 usec()const{return _usec;}
    inline quint16 code()const{return _code;}
    inline CommunicateCoreUnderlying::BubbleDeviceId deviceId()const{return _deviceId;}
    inline QString recDateTime()const{return _recDateTime;}
    inline void setRecDateTime(const QString &value){_recDateTime = value;}
private:    
    quint32 _usec;
    quint16 _code;
    CommunicateCoreUnderlying::BubbleDeviceId _deviceId;
    QString _recDateTime;
};
Q_DECLARE_METATYPE(BubbleMeasureFlightTime_Command_Response)
#endif // BUBBLEMEASUREFLIGHTTIME_COMMAND_RESPONSE_H
