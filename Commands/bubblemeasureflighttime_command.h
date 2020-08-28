#ifndef BUBBLEMEASUREFLIGHTTIME_COMMAND_H
#define BUBBLEMEASUREFLIGHTTIME_COMMAND_H
#include "command.h"
#include <memory>
/**
* @projectName   SITS
* @brief         气泡飞行时间测试命令
* @author        YangAn
* @date          2020-07-28
* @Email         yangan@AutoBio.com.cn
*/
class BubbleMeasureFlightTime_Command : public Command
{
    Q_OBJECT
public:
    BubbleMeasureFlightTime_Command();
    BubbleMeasureFlightTime_Command(InstrumentOperator* operate,  Response *response, int msec, quint8 upstream, quint8 downstream, bool edge, quint32 maxlitch_msec, int timeout_msec, QString key = "", bool async = false, int delayMs = 0);
    BubbleMeasureFlightTime_Command(InstrumentOperator* operate,  Response *response, int msec, CommunicateCoreUnderlying::BubbleDeviceId deviceId, QString key = "", bool async = false, int delayMs = 0);
public:
    inline quint8 upstream(){return _upstream;}
    inline quint8 downstream(){return _downstream;}
    inline bool edge(){return _edge;}
    inline quint32 maxglich_msec(){return _maxglitch_msec;}
    inline quint32 timeout_msec(){return _timeout_msec;}
    inline CommunicateCoreUnderlying::BubbleDeviceId deviceId()const{return _deviceId;}
    void receiveResponse(QByteArray pkg) override;
protected:
    bool package(QByteArray& arr) override;
    bool packageToResponse(QByteArray& arr) override;
private:
    quint8 _upstream, _downstream;
    bool _edge;
    quint32 _maxglitch_msec;
    int _timeout_msec;
    CommunicateCoreUnderlying::BubbleDeviceId _deviceId;
};

#endif // BUBBLEMEASUREFLIGHTTIME_COMMAND_H
