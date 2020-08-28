#ifndef ZSTAGESETHEIGHT_COMMAND_H
#define ZSTAGESETHEIGHT_COMMAND_H
#include "command.h"

class ZStageSetHeight_Command : public Command
{
    Q_OBJECT
public:
    ZStageSetHeight_Command();
    ZStageSetHeight_Command(InstrumentOperator* operate,  Response *response, int msec, int sensors, QVector<int> &height_nm, quint32 timeout_msec);
public:
    inline int sensors()const{return _sensors;}
    inline const QVector<int> &height_nm()const{return _height_nm;}
    inline quint32 timeout_msec()const{return _timeout_msec;}
protected:
    bool package(QByteArray& arr) override;
    bool packageToResponse(QByteArray& arr) override;
private:
    int _sensors;
    QVector<int> _height_nm;
    quint32 _timeout_msec;
};

#endif // ZSTAGESETHEIGHT_COMMAND_H
