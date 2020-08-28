#ifndef BUBBLEMEASUREVOLUME_COMMAND_H
#define BUBBLEMEASUREVOLUME_COMMAND_H

#include <QObject>
#include "command.h"
class BubbleMeasureVolume_Command:Command
{
    Q_OBJECT
public:
    BubbleMeasureVolume_Command();
    BubbleMeasureVolume_Command(InstrumentOperator* operate,  Response *response, int msec, quint8 sensorId);
public:
    inline quint8 sensorId(){return _sensorId;}
protected:
    bool package(QByteArray& arr) override;
    bool packageToResponse(QByteArray& arr) override;
private:
    const quint8 Waste1ID = 0x04;
    const quint8 Waste2ID = 0x08;
    const quint8 LaneA = 0x01;
    const quint8 LaneB = 0x02;
private:
    quint8 _sensorId;
};

#endif // BUBBLEMEASUREVOLUME_COMMAND_H
