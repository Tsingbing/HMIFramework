#include "Toolbox.h"
#include "VehicleManager.h"

Toolbox::Toolbox(QObject *parent)
    : QObject(parent)
{
    _vehicleManager = new VehicleManager(this);
}

void Toolbox::setChildToolboxes()
{
    _vehicleManager->setToolbox(this);
}
