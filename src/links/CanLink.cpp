#include "CanLink.h"
#include <QDebug>
QString CanLink::getName() const
{

}

bool CanLink::isConnected() const
{

}

CanLink::CanLink()
{

}

void CanLink::_writeBytes(const QByteArray data)
{

}

void CanLink::_readBytes()
{
    if (!_port)
        return;

    while (_port->framesAvailable()) {
        const QCanBusFrame frame = _port->readFrame();

        QString view;
        if (frame.frameType() == QCanBusFrame::ErrorFrame)
            view = _port->interpretErrorFrame(frame);
        else
            view = frame.toString();

        const QString time = QString::fromLatin1("%1.%2  ")
                .arg(frame.timeStamp().seconds(), 10, 10, QLatin1Char(' '))
                .arg(frame.timeStamp().microSeconds() / 100, 4, 10, QLatin1Char('0'));

        //const QString flags = frameFlags(frame);

        //processCanData(frame);
        //  m_ui->receivedMessagesEdit->append(time + flags + view);
        //qDebug() << "QCanBusFrame " << view;
    }
}
/// Performs the actual hardware port connection.
///     @param[out] error if failed
///     @param[out] error string if failed
/// @return success/fail
bool CanLink::_hardwareConnect(QCanBusDevice::CanBusError &error, QString &errorString)
{
    _port = QCanBus::instance()->createDevice(QStringLiteral("socketcan"), QStringLiteral("can0"), &errorString);
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
