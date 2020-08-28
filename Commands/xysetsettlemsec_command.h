#ifndef XYSETSETTLEMSEC_COMMAND_H
#define XYSETSETTLEMSEC_COMMAND_H
#include "command.h"

class XYSetSettleMsec_Command : public Command
{
    Q_OBJECT
public:
    XYSetSettleMsec_Command();
    XYSetSettleMsec_Command(InstrumentOperator* operate,  Response *response, int msec, quint32 moveMsec);
public:
    inline quint32 moveMsec()const{return  _moveMsec;}
protected:
    bool package(QByteArray& arr) override;
    bool packageToResponse(QByteArray& arr) override;
private:
    quint32 _moveMsec;
};

#endif // XYSETSETTLEMSEC_COMMAND_H
