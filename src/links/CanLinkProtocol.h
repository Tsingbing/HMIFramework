#ifndef CANLINKPROTOCOL_H
#define CANLINKPROTOCOL_H

#include "Toolbox.h"
#include "VehicleManager.h"
#include "XApplication.h"
#include <QCanBusFrame>
#include <QObject>

class CanLinkProtocol : public Tool
{
    Q_OBJECT
public:
    explicit CanLinkProtocol(XApplication* app, Toolbox* toolbox);
    ~CanLinkProtocol() override;

    // Override from QGCTool
    void setToolbox(Toolbox* toolbox) override;

    /** @brief Get the protocol version */
    QString getVersion() { return "1.2"; }
signals:

public slots:
    /** @brief Receive bytes from a communication interface */
    void receiveBytes(QCanBusFrame canbusframe);

private:
    Vehicle* ve;
};

#endif // CANLINKPROTOCOL_H
