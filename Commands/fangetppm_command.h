#ifndef FANGETPPM_COMMAND_H
#define FANGETPPM_COMMAND_H
#include "command.h"
#include "globals/enums.h"

using namespace Peripheral_Eauipment;
class FanGetPPM_Command : public Command
{
    Q_OBJECT
public:
    FanGetPPM_Command();
    FanGetPPM_Command(InstrumentOperator* operate,  Response *response, int msec, FanType fanType);
public:
    inline FanType fanType()const{return _fanType;}
protected:
    bool package(QByteArray& arr) override;
    bool packageToResponse(QByteArray& arr) override;
private:
    FanType _fanType;
};

#endif // FANGETPPM_COMMAND_H
