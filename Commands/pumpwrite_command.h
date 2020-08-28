#ifndef PUMPWRITE_COMMAND_H
#define PUMPWRITE_COMMAND_H
#include "command.h"

class PumpWrite_Command : public Command
{
    Q_OBJECT
public:
    PumpWrite_Command();
    PumpWrite_Command(InstrumentOperator* operate,  Response *response, int msec, QVector<quint8>& data, quint32 num);
public:
    inline const QVector<quint8>& data()const{return _data;}
    inline quint32 num()const{return _num;}
    void receiveResponse(QByteArray pkg) override;
protected:
    bool package(QByteArray& arr) override;
    bool packageToResponse(QByteArray& arr) override;
private:
    QVector<quint8> _data;
    quint32 _num;
};

#endif // PUMPWRITE_COMMAND_H
