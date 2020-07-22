#include "VehicleManager.h"
#include "Vehicle.h"

VehicleManager::VehicleManager(Toolbox *toolbox)
    : Tool(toolbox)
{

}

void VehicleManager::setToolbox(Toolbox *toolbox)
{
    Tool::setToolbox(toolbox);

    _activeVehicle = new Vehicle(this);
}
