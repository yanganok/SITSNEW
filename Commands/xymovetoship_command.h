#ifndef XYMOVETOSHIP_COMMAND_H
#define XYMOVETOSHIP_COMMAND_H
#include "command.h"

class XYMoveToShip_Command : public Command
{
    Q_OBJECT
public:
    XYMoveToShip_Command();
    XYMoveToShip_Command(InstrumentOperator* operate,  Response *response, int msec);
protected:
    bool package(QByteArray& arr) override;
    bool packageToResponse(QByteArray& arr) override;
};

#endif // XYMOVETOSHIP_COMMAND_H
