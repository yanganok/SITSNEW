#ifndef FANONOFF_COMMAND_H
#define FANONOFF_COMMAND_H
#include "command.h"
#include "globals/enums.h"

using namespace Peripheral_Eauipment;
class FanOnOff_Command : public Command
{
public:
    FanOnOff_Command();
    FanOnOff_Command(InstrumentOperator* operate,  Response *response, int msec, FanType fanType, bool on);
public:
    inline FanType fanType()const{return _fanType;}
    inline bool on()const{return _on;}
protected:
    bool package(QByteArray& arr) override;
    bool packageToResponse(QByteArray& arr) override;
private:
    FanType _fanType;
    bool _on;
};

#endif // FANONOFF_COMMAND_H
