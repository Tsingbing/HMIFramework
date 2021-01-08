#include "Toolbox.h"
#include "FactSystem.h"
#include "LinkManager.h"
#include "SettingsManager.h"
#include "VehicleManager.h"
#include "XApplication.h"

Toolbox::Toolbox(XApplication* app)
{
    _settingsManager = new SettingsManager(app, this);
    _factSystem      = new FactSystem(app, this);
    _linkManager     = new LinkManager(app, this);
    _vehicleManager  = new VehicleManager(app, this);
    _canLinkProtocol = new CanLinkProtocol(app, this);
}

void Toolbox::setChildToolboxes()
{
    // SettingsManager must be first so settings are available to any subsequent tools
    _settingsManager->setToolbox(this);
    _factSystem->setToolbox(this);
    _linkManager->setToolbox(this);
    _vehicleManager->setToolbox(this);
    _canLinkProtocol->setToolbox(this);
}
