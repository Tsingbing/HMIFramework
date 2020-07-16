#ifndef VEHICLEMANAGER_H
#define VEHICLEMANAGER_H

#include <QObject>
#include <Tool.h>
#include <Toolbox.h>
class Vehicle;

class VehicleManager : public Tool
{
    Q_OBJECT

public:
    VehicleManager(Toolbox* toolbox);

    // Override from QGCTool
    virtual void setToolbox(Toolbox *toolbox);

private:
    Vehicle*    _activeVehicle;

};

#endif // VEHICLEMANAGER_H
