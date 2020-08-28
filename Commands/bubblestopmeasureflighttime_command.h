#ifndef BUBBLESTOPMEASUREFLIGHTTIME_COMMAND_H
#define BUBBLESTOPMEASUREFLIGHTTIME_COMMAND_H
#include "command.h"

class BubbleStopMeasureFlightTime_Command : public Command
{
public:
    BubbleStopMeasureFlightTime_Command();
    BubbleStopMeasureFlightTime_Command(InstrumentOperator* operate,  Response *response, int msec, CommunicateCoreUnderlying::BubbleDeviceId deviceId);
public:
    inline CommunicateCoreUnderlying::BubbleDeviceId deviceId()const{return _deviceId;}
protected:
    bool package(QByteArray& arr) override;
    bool packageToResponse(QByteArray& arr) override;
private:
    CommunicateCoreUnderlying::BubbleDeviceId _deviceId;
};

#endif // BUBBLESTOPMEASUREFLIGHTTIME_COMMAND_H
