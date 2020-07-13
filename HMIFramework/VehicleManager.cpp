#include "VehicleManager.h"
#include "Vehicle.h"

void VehicleManager::setToolbox(Toolbox *toolbox)
{
    //Tool::setToolbox(toolbox);

    _activeVehicle = new Vehicle(this);
}
