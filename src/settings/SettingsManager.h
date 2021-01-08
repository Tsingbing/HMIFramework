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

    Q_PROPERTY(QObject* appSettings READ appSettings CONSTANT)

    // Override from Tool
    virtual void setToolbox(Toolbox* toolbox);

    AppSettings* appSettings(void) { return _appSettings; }
    Q_PROPERTY(QString id READ id CONSTANT)
    QString id() { return "10QQ0"; }

private:
    AppSettings* _appSettings;
};

#endif // SETTINGSMANAGER_H
