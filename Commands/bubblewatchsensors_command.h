#ifndef BUBBLEWATCHSENSORS_COMMAND_H
#define BUBBLEWATCHSENSORS_COMMAND_H
#include "command.h"

class BubbleWatchSensors_Command : public Command
{
public:
    BubbleWatchSensors_Command();
    BubbleWatchSensors_Command(InstrumentOperator* operate,  Response *response, int msec, int sensor1, int sensor2, int max_period_msec);
public:
    inline int sensor1()const{return _sensor1;}
    inline int sensor2()const{return _sensor2;}
    inline int max_period_msec()const{return _max_period_msec;}
protected:
    bool package(QByteArray& arr) override;
    bool packageToResponse(QByteArray& arr) override;
private:
    int _sensor1, _sensor2, _max_period_msec;
};

#endif // BUBBLEWATCHSENSORS_COMMAND_H
