#ifndef CAMERASTORELEDGAINS_COMMAND_H
#define CAMERASTORELEDGAINS_COMMAND_H
#include "command.h"
/**
* @projectName   SITS
* @brief         摘要
* @author        YangAn
* @date          2020-07-01
* @Email         yangan@AutoBio.com.cn
*/
class CameraStoreLEDGains_Command:public Command
{
    Q_OBJECT
public:    
    CameraStoreLEDGains_Command();
    CameraStoreLEDGains_Command(InstrumentOperator* operate,  Response *response, int msec, QVector<quint8>& red_gains, QVector<quint8>& grn_gains);
public:
    inline const QVector<quint8>& red_gains()const{return _red_gains;}
    inline const QVector<quint8>& grn_gains()const{return _grn_gains;}
private:
    QVector<quint8> _red_gains;
    QVector<quint8> _grn_gains;
protected:
    bool package(QByteArray& arr) override;
    bool packageToResponse(QByteArray& arr) override;
};

#endif // CAMERASTORELEDGAINS_COMMAND_H
