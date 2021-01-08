#include "HMIQmlGlobal.h"

HMIQmlGlobal::HMIQmlGlobal(XApplication* app, Toolbox* toolbox)
    : Tool(app, toolbox)
{
}

HMIQmlGlobal::~HMIQmlGlobal()
{
}

void HMIQmlGlobal::setToolbox(Toolbox* toolbox)
{
    Tool::setToolbox(toolbox);

    _vehicleManager  = toolbox->vehicleManager();
    _settingsManager = toolbox->settingsManager();
}
