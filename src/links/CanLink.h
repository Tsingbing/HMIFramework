#ifndef CANLINK_H
#define CANLINK_H

#include <QObject>
#include "LinkInterface.h"
#include <QCanBusDevice>
#include <QCanBus>

class CanLinkConfiguration : public QObject
{
    Q_OBJECT
public:
    CanLinkConfiguration(const QString& name);
    CanLinkConfiguration(CanLinkConfiguration *config);
    ~CanLinkConfiguration();

    QString pluginName(){return _pluginName;}
    QString deviceInterfaceName(){return _deviceInterfaceName;}

private:
private:
    QString _pluginName;
    QString _deviceInterfaceName;
};

class CanLink : public LinkInterface
{
    Q_OBJECT
public:
    QString getName() const;
    bool    isConnected() const override;
    CanLink(CanLinkConfiguration& config);
    void writeCanFrame(const QCanBusFrame &frame);

private:
    // From LinkInterface
    bool    _connect                (void) override;
    void    _disconnect             (void) override;

private slots:
    void _writeBytes(const QByteArray) override;

    void _readBytes(void);
    bool _hardwareConnect(QCanBusDevice::CanBusError& error, QString& errorString);

signals:
    void canframesRecived(LinkInterface* link, QCanBusFrame data);

public slots:

private:
    QCanBusDevice *_port = nullptr;
    CanLinkConfiguration *_canConfig;
};

#endif // CANLINK_H
