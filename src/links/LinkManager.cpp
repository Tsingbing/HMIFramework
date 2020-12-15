#include "LinkManager.h"
#include <QDebug>
#include "Toolbox.h"

LinkManager::LinkManager(XApplication* app, Toolbox *toolbox)
    : Tool(app,toolbox)
{

}

LinkManager::~LinkManager()
{

}

void LinkManager::setToolbox(Toolbox *toolbox)
{
    Tool::setToolbox(toolbox);

    _canlinkProtocol = toolbox->canLinkProtocol();

    _canlink = new CanLink();
    if (!_canlink) {
        qDebug() << "Internal error";
    }

    // Initialize the connection
    if (_canlink->Connect()) {
        qDebug() << "can0 Connected";
    }

    connect(_canlink, &CanLink::canframesRecived, _canlinkProtocol,   &CanLinkProtocol::receiveBytes);
}
