#ifndef CANLINK_H
#define CANLINK_H

#include <QObject>
#include "LinkInterface.h"
#include <QCanBusDevice>
#include <QCanBus>

class CanLink : public LinkInterface
{
    Q_OBJECT
public:
    QString getName() const;
    bool    isConnected() const;
    CanLink();

private slots:
    void _writeBytes(const QByteArray data);
    void _readBytes(void);
    bool _hardwareConnect(QCanBusDevice::CanBusError& error, QString& errorString);
signals:

public slots:

private:
    QCanBusDevice *_port = nullptr;
};

#endif // CANLINK_H
