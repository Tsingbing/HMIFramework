#include "Toolbox.h"
#include "VehicleManager.h"
#include "LinkManager.h"

Toolbox::Toolbox(QObject *parent)
    : QObject(parent)
{
    _vehicleManager = new VehicleManager(this);
    _linkManager  = new LinkManager(this);
}

void Toolbox::setChildToolboxes()
{
    _vehicleManager->setToolbox(this);
    _linkManager->setToolbox(this);
}
