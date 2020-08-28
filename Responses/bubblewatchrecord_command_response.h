#ifndef BUBBLEWATCHRECORD_COMMAND_H
#define BUBBLEWATCHRECORD_COMMAND_H
#include <QVector>
#include "response.h"

class BubbleWatchRecord_Command_Response : Response
{
public:
    BubbleWatchRecord_Command_Response();
    BubbleWatchRecord_Command_Response(quint32 timestamp_msec, int sensor, int sensor_polarity, uint interval_usec, QVector<int>& pressure);
public:
    inline quint32 timestamp_msec()const{return _timestamp_msec;}
    inline quint32 interval_usec()const{return _interval_usec;}
    inline int sensor()const{return _sensor;}
    inline int sensor_polarity()const{return _sensor_polarity;}
    inline const QVector<int>& pressure()const{return _pressure;}
private:
    quint32 _timestamp_msec, _interval_usec;
    int _sensor, _sensor_polarity;
    QVector<int> _pressure;
};
Q_DECLARE_METATYPE(BubbleWatchRecord_Command_Response)

#endif // BUBBLEWATCHRECORD_COMMAND_H
