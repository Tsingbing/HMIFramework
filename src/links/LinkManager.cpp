#include "LinkManager.h"
#include <QDebug>
#include "Toolbox.h"


LinkManager::LinkManager(Toolbox *toolbox)
    : Tool(toolbox)
{
    _canlinkProtocol = new CanLinkProtocol(this);
    createConnectedLink(nullptr);

}

LinkManager::~LinkManager()
{

}

LinkInterface *LinkManager::createConnectedLink(CanLinkConfiguration *config)
{
//    if (!config) {
//        qWarning() << "LinkManager::createConnectedLink called with nullptr config";
//        return nullptr;
//    }
    CanLinkConfiguration *config1 = new CanLinkConfiguration("can0");
    _canlink = new CanLink(*config1);
    connect(_canlink, &CanLink::canframesRecived, _canlinkProtocol,   &CanLinkProtocol::receiveBytes);
    connectLink(_canlink);
}

bool LinkManager::connectLink(LinkInterface *link)
{
    if (link) {
        return link->_connect();
    } else {
        qDebug() << "Internal error";
        return false;
    }
}

void LinkManager::disconnectLink(LinkInterface *link)
{
    if (!link) {
        return;
    }

    link->_disconnect();
}

void LinkManager::setToolbox(Toolbox *toolbox)
{
    Tool::setToolbox(toolbox);

}
