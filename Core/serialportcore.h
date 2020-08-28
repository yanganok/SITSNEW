#ifndef SERIALPORTCORE_H
#define SERIALPORTCORE_H
#include <QtSerialPort/QSerialPort>
#include <QSerialPortInfo>
#include <memory>
#include "communicationcore.h"

class SerialPort_CommunicationCore:public CommunicationCore
{
public:
    SerialPort_CommunicationCore();
public slots:
    void doWork() override;
protected:
    void writePackage(const QByteArray &pkg) override;
    bool readPackage() override;
    void createCommunicateDevice() override;
    bool reconnection() override;
private:
    std::shared_ptr<QSerialPort> _serialport;
};

#endif // SERIALPORTCORE_H
