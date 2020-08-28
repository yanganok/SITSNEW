#ifndef CANCELBYID_COMMAND_H
#define CANCELBYID_COMMAND_H
#include "command.h"

class CancelById_Command : public Command
{
    Q_OBJECT
public:
    CancelById_Command();
    CancelById_Command(InstrumentOperator* operate,  Response *response, int msec, int id);
    inline int id()const{return _idCount;}

protected:
    bool package(QByteArray& arr) override;
    bool packageToResponse(QByteArray& arr) override;
private:
    int _idCount;
};

#endif // CANCELBYID_COMMAND_H
