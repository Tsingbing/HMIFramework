#include "SettingsManager.h"

SettingsManager::SettingsManager(XApplication* app, Toolbox *toolbox)
    : Tool(app, toolbox)
{

}

void SettingsManager::setToolbox(Toolbox *toolbox)
{
    _toolbox = toolbox;
}
