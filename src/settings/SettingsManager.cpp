#include "SettingsManager.h"

SettingsManager::SettingsManager(Toolbox *toolbox)
    : Tool(toolbox)
{

}

void SettingsManager::setToolbox(Toolbox *toolbox)
{
    _toolbox = toolbox;
}
