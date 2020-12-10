#ifndef CANLINKPROTOCOL_H
#define CANLINKPROTOCOL_H

#include <QObject>
#include "LinkInterface.h"
#include <QCanBusFrame>

class CanLinkProtocol : public QObject
{
    Q_OBJECT
public:
    explicit CanLinkProtocol(QObject *parent = nullptr);
    /** @brief Get the protocol version */
    QString getVersion() {
        return "1.2";
    }
signals:

public slots:
    /** @brief Receive bytes from a communication interface */
    void receiveBytes(LinkInterface* link, QCanBusFrame canbusframe);
};

#endif // CANLINKPROTOCOL_H
