#include "cancel_command.h"

Cancel_Command::Cancel_Command()
{

}

Cancel_Command::Cancel_Command(InstrumentOperator *operate,  Response *response, int msec, const QString cancel_cmd_name)
    :Command(operate, response, msec), _cancel_cmd_name(cancel_cmd_name)
{

}

QString Cancel_Command::cancel_cmd_name() const
{
    return _cancel_cmd_name;
}

bool Cancel_Command::package(QByteArray &arr)
{
    return true;
}

bool Cancel_Command::packageToResponse(QByteArray &arr)
{
    return true;
}
