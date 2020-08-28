#ifndef BUBBLEMEASUREFLIGHTTIMEMEASUREMODEL_H
#define BUBBLEMEASUREFLIGHTTIMEMEASUREMODEL_H

#include <QObject>
#include <QDateTime>
#include <qqml.h>

class BubbleMeasureFlightTimeMeasureModel:public QObject
{
    Q_OBJECT
    Q_PROPERTY(int id READ id WRITE setId)
    Q_PROPERTY(int usec READ usec WRITE setUsec)
    Q_PROPERTY(QString recDateTime READ recDateTime WRITE setRecDateTime)
    QML_ELEMENT
public:
    BubbleMeasureFlightTimeMeasureModel();
public:
    inline int id()const{return _id;}
    inline int usec()const{return _usec;}
    inline QString recDateTime(){return _recDateTime;}

    inline void setId(int value){_id = value;}
    inline void setUsec(int value){_usec = value;}
    inline void setRecDateTime(QString value){_recDateTime = value;}
private:
    int _id;
    int _usec;
    QString _recDateTime;
};

#endif // BUBBLEMEASUREFLIGHTTIMEMEASUREMODEL_H
