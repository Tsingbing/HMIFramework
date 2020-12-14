#include "CanLink.h"
#include <QDebug>

CanLinkConfiguration::CanLinkConfiguration(const QString &name)
{
    _pluginName =  "socketcan";
    _deviceInterfaceName = "can0";
}

CanLinkConfiguration::CanLinkConfiguration(CanLinkConfiguration* copy)
{
    //_pluginName = copy->_pluginName;
    //_deviceInterfaceName = copy->_deviceInterfaceName;
}

CanLinkConfiguration::~CanLinkConfiguration()
{

}


QString CanLink::getName() const
{

}

bool CanLink::_connect()
{
    qDebug() << "CONNECT CALLED";

    _disconnect();

    QCanBusDevice::CanBusError   error;
    QString                      errorString;

    // Initialize the connection
    if (!_hardwareConnect(error, errorString)) {
        //qDebug() << "can0 jianli";
        return false;
    }
    return true;
}

void CanLink::_disconnect()
{
    if (_port) {
        _port->deleteLater();
        _port = nullptr;
    }
}

void CanLink::_writeBytes(const QByteArray)
{

}

bool CanLink::isConnected() const
{

}

CanLink::CanLink(CanLinkConfiguration& config)
    : _canConfig(&config)
{

}

void CanLink::writeCanFrame(const QCanBusFrame &frame)
{
    if (!_port)
        return;

    _port->writeFrame(frame);
}

void CanLink::_readBytes()
{
    if (!_port)
        return;
    //qDebug() << "_readBytes " ;
    while (_port->framesAvailable()) {
        const QCanBusFrame frame = _port->readFrame();
        emit canframesRecived(this, frame);
    }
}
/// Performs the actual hardware port connection.
///     @param[out] error if failed
///     @param[out] error string if failed
/// @return success/fail
bool CanLink::_hardwareConnect(QCanBusDevice::CanBusError &error, QString &errorString)
{
    QString pluginName = _canConfig->pluginName();
    QString deviceInterfaceName = _canConfig->deviceInterfaceName();

    _port = QCanBus::instance()->createDevice(pluginName, deviceInterfaceName, &errorString);
    connect(_port, &QCanBusDevice::framesReceived, this, &CanLink::_readBytes);
    if (!_port) {
        error = _port->error();
        delete _port;
        _port = nullptr;
        return false;
    } else {
        _port->connectDevice();
    }
    return true;
}
