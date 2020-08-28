#include "serialportcore.h"

SerialPort_CommunicationCore::SerialPort_CommunicationCore()
{

}

void SerialPort_CommunicationCore::doWork()
{
    CommunicationCore::doWork();
}

void SerialPort_CommunicationCore::writePackage(const QByteArray &pkg)
{
    int sendLen = _serialport->write(pkg);
    bool isWrited = _serialport->waitForBytesWritten(100);
    CommunicationCore::writePackage(pkg);
    DebugOut(QStringLiteral("发送成功"));
}

bool SerialPort_CommunicationCore::readPackage()
{
    QByteArray bytes = _serialport->readAll();
    _receiveBuffer.append(bytes);
    bool reading = false;
    while (_serialport->waitForReadyRead(10))
    {
        reading = true;
        QByteArray bytes = _serialport->readAll();
//#ifdef DEBUG
//        QString s = BytesToAny::QByteArrayToHexString(bytes);
//#endif
//        if(s == "")
//            DebugOut(s);
//        DebugOut(QStringLiteral("send:%1").arg(s));
        _receiveBuffer.append(bytes);
    }
    return reading;
}

void SerialPort_CommunicationCore::createCommunicateDevice()
{
    _serialport = std::shared_ptr<QSerialPort>(new QSerialPort(), [this](QSerialPort *p){
            //this->disconnect(p, &QSerialPort::readyRead, this, &CommunicationCore::onReadyRead);
            p->close();
            delete p;
    });
    //connect(_serialport.get(), &QSerialPort::readyRead, this, &CommunicationCore::onReadyRead, Qt::DirectConnection);
    DebugOut(QString("线程Id:%1").arg((qlonglong)QThread::currentThreadId()));

    QString portName = IniFile::ReadIniFile(QString("SerialPort"), QString("PortName"), QVariant(QString("COM1")), QString(IniFile::IniFileName)).value<QString>();
    QSerialPort::BaudRate baudrate = IniFile::ReadIniFile(QString("SerialPort"), QString("BaudRate"), QVariant(QSerialPort::Baud9600), QString(IniFile::IniFileName)).value<QSerialPort::BaudRate>();
    QSerialPort::DataBits dataBits = IniFile::ReadIniFile(QString("SerialPort"), QString("DataBits"), QVariant(QSerialPort::Data8), QString(IniFile::IniFileName)).value<QSerialPort::DataBits>();
    QSerialPort::StopBits stopBits = IniFile::ReadIniFile(QString("SerialPort"), QString("StopBits"), QVariant(QSerialPort::OneStop), QString(IniFile::IniFileName)).value<QSerialPort::StopBits>();
    QSerialPort::Parity parity = IniFile::ReadIniFile(QString("SerialPort"), QString("Parity"), QVariant(QSerialPort::NoParity), QString(IniFile::IniFileName)).value<QSerialPort::Parity>();
    _serialport->setPortName(portName);
    _serialport->setBaudRate(baudrate);
    _serialport->setDataBits(dataBits);
    _serialport->setStopBits(stopBits);
    _serialport->setParity(parity);
}

bool SerialPort_CommunicationCore::reconnection()
{
    _locker.lock();
    bool isConnectioned = false;
//    if(_serialport->error() == QSerialPort::TimeoutError)
//    {
//        _serialport->close();
//    }
    QList<QSerialPortInfo> serialportInfos = QSerialPortInfo::availablePorts();
    bool isExists = false;
    for(auto el : serialportInfos)
    {
        if(el.portName() == _serialport->portName())
        {
            isExists = true;
            break;
        }
    }
    if(isExists)
    {
        _serialport->clearError();
        if(!_serialport->isOpen())
        {
            //_communicateStatus = CommunicateCoreUnderlying::CommunicateStatus::CLOSE;
            _condition.wait(&_locker, 500);
            QString portName = IniFile::ReadIniFile(QString("SerialPort"), QString("PortName"), QVariant(QString("COM1")), QString(IniFile::IniFileName)).value<QString>();
            QSerialPort::BaudRate baudrate = IniFile::ReadIniFile(QString("SerialPort"), QString("BaudRate"), QVariant(QSerialPort::Baud9600), QString(IniFile::IniFileName)).value<QSerialPort::BaudRate>();
            QSerialPort::DataBits dataBits = IniFile::ReadIniFile(QString("SerialPort"), QString("DataBits"), QVariant(QSerialPort::Data8), QString(IniFile::IniFileName)).value<QSerialPort::DataBits>();
            QSerialPort::StopBits stopBits = IniFile::ReadIniFile(QString("SerialPort"), QString("StopBits"), QVariant(QSerialPort::OneStop), QString(IniFile::IniFileName)).value<QSerialPort::StopBits>();
            QSerialPort::Parity parity = IniFile::ReadIniFile(QString("SerialPort"), QString("Parity"), QVariant(QSerialPort::NoParity), QString(IniFile::IniFileName)).value<QSerialPort::Parity>();
            _serialport->setPortName(portName);
            _serialport->setBaudRate(baudrate);
            _serialport->setDataBits(dataBits);
            _serialport->setStopBits(stopBits);
            _serialport->setParity(parity);
            _serialport->setReadBufferSize(1);
            _serialport->open(QIODevice::ReadWrite);
        }
        if(isConnectioned = _serialport->isOpen())
        {
            _communicateStatus = CommunicateCoreUnderlying::CommunicateStatus::OPENED;
        }
        else
        {
            QSerialPort::SerialPortError error = _serialport->error();
            if(error == QSerialPort::SerialPortError::PermissionError)
            {
                _communicateStatus = CommunicateCoreUnderlying::CommunicateStatus::OCCUPY;
            }
            else if(error == QSerialPort::SerialPortError::DeviceNotFoundError)
            {
                _communicateStatus = CommunicateCoreUnderlying::CommunicateStatus::ISNOTEXISTS;
            }
        }
    }
    else
    {
        _serialport->close();
        _communicateStatus = CommunicateCoreUnderlying::CommunicateStatus::ISNOTEXISTS;
    }
    _locker.unlock();
    return isConnectioned;
}
