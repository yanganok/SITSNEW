#ifndef LOGREPLY_COMMAND_H
#define LOGREPLY_COMMAND_H
#include "command.h"

class LogReplay_Command : public Command
{
    Q_OBJECT
public:
    LogReplay_Command();
    LogReplay_Command(InstrumentOperator* operate,  Response *response, int msec,
                     QString name, quint32 maxrecs, quint32 minseqnum, bool only_new);
public:
    inline const QString &name()const{return _name;}
    inline quint32 maxrecs()const{return _maxrecs;}
    inline quint32 minseqnum()const{return _minseqnum;}
    inline bool only_new()const{return _only_new;}
private:
    QString _name;
    quint32 _maxrecs;
    quint32 _minseqnum;
    bool _only_new;
};

#endif // LOGREPLY_COMMAND_H
