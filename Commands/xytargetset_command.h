#ifndef XYTARGETSSET_COMMAND_H
#define XYTARGETSSET_COMMAND_H
#include "command.h"

class XYTargetSet_Command : public Command
{
    Q_OBJECT
public:
    XYTargetSet_Command();
    XYTargetSet_Command(InstrumentOperator* operate,  Response *response, int msec, quint32 index, int x_nm, int y_nm);
public:
    inline quint32 index()const{return _index;}
    inline int x_nm()const{return _x_nm;}
    inline int y_nm()const{return _y_nm;}
protected:
    bool package(QByteArray& arr) override;
    bool packageToResponse(QByteArray& arr) override;
private:
    quint32 _index;
    int _x_nm;
    int _y_nm;
};

#endif // XYTARGETSSET_COMMAND_H
