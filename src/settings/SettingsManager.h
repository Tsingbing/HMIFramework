#ifndef SETTINGSMANAGER_H
#define SETTINGSMANAGER_H

#include "AppSettings.h"
#include "Tool.h"
#include "Toolbox.h"
#include <QObject>

class SettingsManager : public Tool
{
    Q_OBJECT
public:
    SettingsManager(XApplication* app, Toolbox* toolbox);

    // Override from Tool
    virtual void setToolbox(Toolbox* toolbox);

    AppSettings* appSettings(void) { return _appSettings; }

private:
    AppSettings* _appSettings;
};

#endif // SETTINGSMANAGER_H
