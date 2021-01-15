#ifndef HMIQMLGLOBAL_H
#define HMIQMLGLOBAL_H

#include "SettingsManager.h"
#include "Tool.h"
#include "Toolbox.h"
#include "VehicleManager.h"
#include "XApplication.h"
#include <QObject>

class HMIQmlGlobal : public Tool
{
    Q_OBJECT
public:
    HMIQmlGlobal(XApplication* app, Toolbox* toolbox);
    ~HMIQmlGlobal();

    Q_PROPERTY(VehicleManager* vehicleManager READ vehicleManager CONSTANT)
    Q_PROPERTY(SettingsManager* settingsManager READ settingsManager CONSTANT)
    Q_PROPERTY(QString appName READ appName CONSTANT)
    Q_PROPERTY(QString hmiVersion READ hmiVersion CONSTANT)
    Q_PROPERTY(qreal zOrderTopMost READ zOrderTopMost CONSTANT) ///< z order for top most items, toolbar, main window sub view

    // Property accesors
    QString          appName() { return XApp()->applicationName(); }
    VehicleManager*  vehicleManager() { return _vehicleManager; }
    SettingsManager* settingsManager() { return _settingsManager; }
    // Overrides from Tool
    virtual void setToolbox(Toolbox* toolbox);

    qreal zOrderTopMost() const { return 1000; }

    QString hmiVersion() const
    {
        QString versionStr = XApp()->applicationVersion();
        return versionStr;
    }

private:
    VehicleManager*  _vehicleManager  = nullptr;
    SettingsManager* _settingsManager = nullptr;
};

#endif // HMIQMLGLOBAL_H
