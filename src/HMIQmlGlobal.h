#ifndef HMIQMLGLOBAL_H
#define HMIQMLGLOBAL_H

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
    Q_PROPERTY(QString appName READ appName CONSTANT)

    // Property accesors
    QString         appName() { return XApp()->applicationName(); }
    VehicleManager* vehicleManager() { return _vehicleManager; }

    // Overrides from Tool
    virtual void setToolbox(Toolbox* toolbox);

private:
    VehicleManager* _vehicleManager = nullptr;
};

#endif // HMIQMLGLOBAL_H
