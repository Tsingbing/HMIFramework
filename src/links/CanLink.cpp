#include "CanLink.h"
#include <QDebug>

bool CanLink::Connect()
{
    //qDebug() << "CONNECT CALLED";
    Disconnect();

    //QCanBusDevice::CanBusError error;
    QString errorString;

    //    if (!_hardwareConnect(error, errorString))
    //    {
    //        return false;
    //    }
    return false;
}

void CanLink::Disconnect()
{
    if (_port)
    {
        _port->deleteLater();
        _port = nullptr;
    }
}

CanLink::CanLink() {}

void CanLink::writeCanFrame(const QCanBusFrame& frame)
{

    if (!_port)
        return;
    qDebug() << "writeCanFrame";
    _port->writeFrame(frame);
}

void CanLink::_readBytes()
{
    if (!_port)
        return;
    // qDebug() << "_readBytes " ;
    while (_port->framesAvailable())
    {
        const QCanBusFrame frame = _port->readFrame();
        emit               canframesRecived(frame);
    }
}

/// Performs the actual hardware port connection.
///     @param[out] error if failed
///     @param[out] error string if failed
/// @return success/fail
bool CanLink::_hardwareConnect(QCanBusDevice::CanBusError& error, QString& errorString)
{
    _port = QCanBus::instance()->createDevice(QStringLiteral("socketcan"), QStringLiteral("can0"),
                                              &errorString);

    if (!_port)
    {
        error = _port->error();
        delete _port;
        _port = nullptr;
        return false;
    }
    else
    {
        connect(_port, &QCanBusDevice::framesReceived, this, &CanLink::_readBytes);
        _port->connectDevice();
    }
    return true;
}
