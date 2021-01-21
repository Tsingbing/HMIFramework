#include "CanLinkProtocol.h"
#include "Vehicle.h"
#include <QDebug>

CanLinkProtocol::CanLinkProtocol(XApplication* app, Toolbox* toolbox)
    : Tool(app, toolbox)
{
}

CanLinkProtocol::~CanLinkProtocol()
{
}

void CanLinkProtocol::setToolbox(Toolbox* toolbox)
{
    Tool::setToolbox(toolbox);

    //_linkMgr =               _toolbox->linkManager();
    ve = toolbox->vehicleManager()->activeVehicle();
}

void CanLinkProtocol::receiveBytes(QCanBusFrame canbusframe)
{
    QString view;

    view = canbusframe.toString();

    const QString time = QString::fromLatin1("%1.%2  ")
                             .arg(canbusframe.timeStamp().seconds(), 10, 10, QLatin1Char(' '))
                             .arg(canbusframe.timeStamp().microSeconds() / 100, 3, 10, QLatin1Char('0'));

    //qCDebug(CanLog) << time << view;

    quint32    frameId = canbusframe.frameId();
    QByteArray payload = canbusframe.payload();

    switch (frameId)
    {
        case 0x01801F09:
        {
            //qDebug() << "payload 0x10F51001: " << payload.toHex(':');
            //系统电压
            ve->supplyVoltageFact()->setRawValue(QVariant((payload.at(0) + (payload.at(1) << 8)) * 0.1));
            ve->fuelLevelFact()->setRawValue(QVariant(payload.at(2)));
            ve->oxygenConcentrationFact()->setRawValue(QVariant(payload.at(3)));
            ve->mainPumpPressureFact()->setRawValue(QVariant((payload.at(4) + (payload.at(5) << 8)) * 0.1));
            ve->combustibleGasConcentrationFact()->setRawValue(QVariant(payload.at(6)));
            ve->ambientTemperaturenFact()->setRawValue(QVariant(payload.at(7) - 20));
        }
        break;
        case 0x18ECFF1C:
        {
            ve->xDegreeFact()->setRawValue(QVariant((payload.at(1) + (payload.at(2) << 8)) * 0.01));
            ve->yDegreeFact()->setRawValue(QVariant((payload.at(3) + (payload.at(4) << 8)) * 0.01));
            ve->rotatingSpeedFact()->setRawValue(QVariant((payload.at(5) + (payload.at(6) << 8))));
            ve->waterTemperatureFact()->setRawValue(QVariant(payload.at(7)));
        }
        break;
        case 0x1CEBFF1C:
        {
            ve->workHoursFact()->setRawValue(QVariant(
                (payload.at(0) + (payload.at(1) << 8) + (payload.at(2) << 16) + (payload.at(3) << 24))));
            ve->oilTemperatureFact()->setRawValue(QVariant(payload.at(4) - 50));
        }
        break;
        case 0x10F58101:
        {
        }
        break;
    }
}
