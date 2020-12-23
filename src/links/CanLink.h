#ifndef CANLINK_H
#define CANLINK_H

#include <QCanBus>
#include <QCanBusDevice>
#include <QObject>

class CanLink : public QObject
{
    Q_OBJECT
public:
    CanLink();
    void writeCanFrame(const QCanBusFrame& frame);
    bool Connect(void);
    void Disconnect(void);

private:
private slots:
    void _readBytes(void);
    bool _hardwareConnect(QCanBusDevice::CanBusError& error, QString& errorString);

signals:
    void canframesRecived(QCanBusFrame data);

public slots:

private:
    QCanBusDevice* _port = nullptr;
};

#endif // CANLINK_H
