#include "VehicleManager.h"
#include "Vehicle.h"

VehicleManager::VehicleManager(XApplication* app, Toolbox* toolbox)
    : Tool(app, toolbox)
{
}

void VehicleManager::setToolbox(Toolbox* toolbox)
{
    Tool::setToolbox(toolbox);

    _activeVehicle = new Vehicle(this);
}
