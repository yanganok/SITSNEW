#ifndef XYTARGETSSET_COMMAND_H
#define XYTARGETSSET_COMMAND_H
#include <QVector>
#include "command.h"

class XYTargetsSet_Command : public Command
{
    Q_OBJECT
public:
    XYTargetsSet_Command();
    XYTargetsSet_Command(InstrumentOperator* operate,  Response *response, int msec, QVector<quint32> &index, QVector<int> &x_nm, QVector<int> &y_nm);
public:
    inline const QVector<quint32> &index()const{return _index;}
    inline const QVector<int> &x_nm()const{return _x_nm;}
    inline const QVector<int> &y_nm()const{return _y_nm;}
protected:
    bool package(QByteArray& arr) override;
    bool packageToResponse(QByteArray& arr) override;
private:
    QVector<quint32> _index;
    QVector<int> _x_nm;
    QVector<int> _y_nm;
};

#endif // XYTARGETSSET_COMMAND_H
