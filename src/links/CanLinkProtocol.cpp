#include "CanLinkProtocol.h"

CanLinkProtocol::CanLinkProtocol(QObject *parent) : QObject(parent)
{

}

void CanLinkProtocol::receiveBytes(LinkInterface *link, QCanBusFrame canbusframe)
{
    
}
