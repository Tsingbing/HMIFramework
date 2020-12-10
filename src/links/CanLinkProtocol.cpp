#include "CanLinkProtocol.h"
#include <QDebug>
CanLinkProtocol::CanLinkProtocol(QObject *parent) : QObject(parent)
{

}

void CanLinkProtocol::receiveBytes(LinkInterface *link, QCanBusFrame canbusframe)
{
    QString view;

    view = canbusframe.toString();

    const QString time = QString::fromLatin1("%1.%2  ")
            .arg(canbusframe.timeStamp().seconds(), 10, 10, QLatin1Char(' '))
            .arg(canbusframe.timeStamp().microSeconds() / 100, 4, 10, QLatin1Char('0'));

    qDebug() << time << view;
}
