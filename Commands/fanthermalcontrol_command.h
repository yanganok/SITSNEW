#ifndef FANTHERMALCONTROL_COMMAND_H
#define FANTHERMALCONTROL_COMMAND_H
#include "command.h"

class FanThermalControl_Command:public Command
{
    Q_OBJECT
public:
    FanThermalControl_Command();
    FanThermalControl_Command(InstrumentOperator* operate,  Response *response, int msec, bool enable);
public:
    inline bool enable()const{return _enable;}
protected:
    bool package(QByteArray& arr) override;
    bool packageToResponse(QByteArray& arr) override;
private:
    bool _enable;
};

#endif // FANTHERMALCONTROL_COMMAND_H
