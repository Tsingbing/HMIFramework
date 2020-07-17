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

    Vehicle*    activeVehicle() {return _activeVehicle;}
    ///< 覆写Tool函数
    virtual void setToolbox(Toolbox *toolbox);

private:
    Vehicle*    _activeVehicle;

};

#endif // VEHICLEMANAGER_H
