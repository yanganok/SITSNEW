#include "miscfwstage_command.h"


MiscFWStage_Command::MiscFWStage_Command()
{

}

MiscFWStage_Command::MiscFWStage_Command(InstrumentOperator *operate,  Response *response, int msec, QString fileName)
    :Command(operate, response, msec), _fileName(fileName)
{

}

bool MiscFWStage_Command::package(QByteArray &arr)
{
    return true;
}

bool MiscFWStage_Command::packageToResponse(QByteArray &arr)
{
    return true;
}
