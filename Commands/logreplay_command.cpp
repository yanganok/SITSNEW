#include "logreplay_command.h"

LogReplay_Command::LogReplay_Command()
{

}

LogReplay_Command::LogReplay_Command(InstrumentOperator *operate,  Response *response, int msec,
                                   QString name, quint32 maxrecs, quint32 minseqnum, bool only_new)
    :Command(operate, response, msec), _name(name), _maxrecs(maxrecs), _minseqnum(minseqnum), _only_new(only_new)
{

}
