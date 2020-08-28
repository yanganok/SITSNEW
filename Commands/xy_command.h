#ifndef XY_COMMAND_H
#define XY_COMMAND_H
#include "command.h"

class XY_Command : public Command
{
    Q_OBJECT
public:
    XY_Command();
    XY_Command(InstrumentOperator* operate, Response *response, int msec = -1);
protected:
    static int _curPos;
};

#endif // XY_COMMAND_H
