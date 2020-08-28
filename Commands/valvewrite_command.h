#ifndef VALVEWRITE_COMMAND_H
#define VALVEWRITE_COMMAND_H
#include <QVector>
#include "command.h"

class ValveWrite_Command : public Command
{
    Q_OBJECT
public:
    ValveWrite_Command();
    ValveWrite_Command(InstrumentOperator* operate,  Response *response, int msec, int valve, QVector<quint8>&data, quint32 num);
public:
    inline int valve()const{return _valve;}
    inline quint32 num()const{return _num;}
    inline const QVector<quint8>& data()const{return _data;}
protected:
    bool package(QByteArray& arr) override;
    bool packageToResponse(QByteArray& arr) override;
private:
    int _valve;
    QVector<quint8> _data;
    quint32 _num;
};

#endif // VALVEWRITE_COMMAND_H
