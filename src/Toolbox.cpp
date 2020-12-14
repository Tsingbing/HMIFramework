#include "XApplication.h"
#include "Toolbox.h"
#include "VehicleManager.h"
#include "LinkManager.h"

Toolbox::Toolbox(XApplication* app)
{
    _linkManager  = new LinkManager(app, this);
    _vehicleManager = new VehicleManager(app, this);
    _canLinkProtocol = new CanLinkProtocol(app, this);
}

void Toolbox::setChildToolboxes()
{
    _linkManager->setToolbox(this);
    _vehicleManager->setToolbox(this);
    _canLinkProtocol->setToolbox(this);
}
