#include "SettingsManager.h"

SettingsManager::SettingsManager(XApplication* app, Toolbox* toolbox)
    : Tool(app, toolbox)
    , _appSettings(nullptr)
{
}

void SettingsManager::setToolbox(Toolbox* toolbox)
{
    _toolbox     = toolbox;
    _appSettings = new AppSettings(this);
}
