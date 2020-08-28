#ifndef LOGGETLIST_COMMAND_H
#define LOGGETLIST_COMMAND_H
#include "command.h"

class LogGetList_Command : public Command
{
    Q_OBJECT
public:
    LogGetList_Command();
    LogGetList_Command(InstrumentOperator* operate,  Response *response, int msec);
protected:
    bool package(QByteArray& arr) override;
    bool packageToResponse(QByteArray& arr) override;
};

#endif // LOGGETLIST_COMMAND_H
