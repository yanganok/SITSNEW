#include "rfidtagvalidation_command.h"

RFIDTagValidation_Command::RFIDTagValidation_Command()
{

}

RFIDTagValidation_Command::RFIDTagValidation_Command(InstrumentOperator *operate,  Response *response, int msec, bool enable_nDisable)
    :Command(operate, response, msec), _enable_nDisable(enable_nDisable)
{

}

bool RFIDTagValidation_Command::package(QByteArray &arr)
{
    return true;
}

bool RFIDTagValidation_Command::packageToResponse(QByteArray &arr)
{
    return true;
}
