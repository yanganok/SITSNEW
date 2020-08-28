#ifndef CAMERASNAPFREE_COMMAND_H
#define CAMERASNAPFREE_COMMAND_H
#include "command.h"

class CameraSnapFree_Command : public Command
{
    Q_OBJECT
public:
    CameraSnapFree_Command();
    CameraSnapFree_Command(InstrumentOperator* operate,  Response *response, int msec, quint32 id);
public:
    inline quint32 id()const{return _idCount;}
protected:
    bool package(QByteArray& arr) override;
    bool packageToResponse(QByteArray& arr);
private:
    quint32 _idCount;
};

#endif // CAMERASNAPFREE_COMMAND_H
