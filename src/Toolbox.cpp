#include "XApplication.h"
#include "Toolbox.h"
#include "VehicleManager.h"
#include "LinkManager.h"
#include "SettingsManager.h"

Toolbox::Toolbox(XApplication* app)
{
    _settingsManager = new SettingsManager(app, this);
    _linkManager  = new LinkManager(app, this);
    _vehicleManager = new VehicleManager(app, this);
    _canLinkProtocol = new CanLinkProtocol(app, this);
}

void Toolbox::setChildToolboxes()
{
    // SettingsManager must be first so settings are available to any subsequent tools
    _settingsManager->setToolbox(this);
    _linkManager->setToolbox(this);
    _vehicleManager->setToolbox(this);
    _canLinkProtocol->setToolbox(this);
}
