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

    //qDebug() << time << view;

    quint32    frameId = canbusframe.frameId();
    QByteArray payload = canbusframe.payload();
    int        value   = 0;
    int        baojing = 0;

    switch (frameId)
    {
        case 0x10F51001:
        {
            //qDebug() << "payload 0x10F51001: " << payload.toHex(':');
            //系统电压
            value         = payload.at(0) + ((payload.at(1) & 0x0F) << 8);
            baojing       = ((payload.at(1) & 0xF0) >> 4);
            double dianya = value * 0.1;
            ve->supplyVoltageFact()->setRawValue(QVariant(dianya));

            //冷却水温
            value          = payload.at(2) + ((payload.at(3) & 0x0F) << 8);
            baojing        = ((payload.at(3) & 0xF0) >> 4);
            double shuiwen = value * 0.1 - 400;

            //发动机转速
            value          = payload.at(4) + ((payload.at(5) & 0x0F) << 8);
            baojing        = ((payload.at(5) & 0xF0) >> 4);
            double zhuansu = value * 1;

            //燃油量
            value              = payload.at(6) + ((payload.at(7) & 0x0F) << 8);
            baojing            = ((payload.at(7) & 0xF0) >> 4);
            double ranyouliang = value * 1;
        }
        break;
        case 0x10F51101:
        {
            //qDebug() << "payload 0x10F51101: " << payload.toHex(':');
            //液压油温
            value         = payload.at(6) + ((payload.at(7) & 0x0F) << 8);
            baojing       = ((payload.at(7) & 0xF0) >> 4);
            double youwen = value * 0.1 - 400;
        }
        break;
        case 0x10F51301:
        {
            //qDebug() << "payload 0x10F51101: " << payload.toHex(':');
            //前泵压力
            value               = payload.at(4) + ((payload.at(5) & 0x0F) << 8);
            baojing             = ((payload.at(5) & 0xF0) >> 4);
            double qianbengyali = value;

            //后泵压力
            value              = payload.at(6) + ((payload.at(7) & 0x0F) << 8);
            baojing            = ((payload.at(7) & 0xF0) >> 4);
            double houbengyali = value;
        }
        break;
        case 0x10F58101:
        {
            //X轴倾角
            value         = payload.at(0);
            int qingjiaoX = value - 50;
            //Y轴倾角
            value         = payload.at(1);
            int qingjiaoY = value - 50;
        }
        break;
    }
}
