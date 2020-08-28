#include "xymovetoship_command.h"

XYMoveToShip_Command::XYMoveToShip_Command()
{

}

XYMoveToShip_Command::XYMoveToShip_Command(InstrumentOperator *operate,  Response *response, int msec)
    :Command(operate, response, msec)
{

}

bool XYMoveToShip_Command::package(QByteArray &arr)
{
    return true;
}

bool XYMoveToShip_Command::packageToResponse(QByteArray &arr)
{
    return true;
}
