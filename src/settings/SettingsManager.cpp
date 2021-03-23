#include "SettingsManager.h"

#include <QQmlEngine>
#include <QtQml>

SettingsManager::SettingsManager(XApplication* app, Toolbox* toolbox)
    : Tool(app, toolbox)
    , _appSettings(nullptr)
{
}

void SettingsManager::setToolbox(Toolbox* toolbox)
{
    Tool::setToolbox(toolbox);
    //QQmlEngine::setObjectOwnership(this, QQmlEngine::CppOwnership);
    //qmlRegisterUncreatableType<SettingsManager>("HMI.SettingsManager", 1, 0, "SettingsManager", "Reference only");

    _toolbox     = toolbox;
    _appSettings = new AppSettings(this);
}
