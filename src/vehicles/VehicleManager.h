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
    VehicleManager(XApplication* app, Toolbox* toolbox);

    Q_PROPERTY(Vehicle* activeVehicle READ activeVehicle WRITE setActiveVehicle NOTIFY activeVehicleChanged)

    Vehicle* activeVehicle() { return _activeVehicle; }
    void     setActiveVehicle(Vehicle* vehicle);

    ///< 覆写Tool函数
    virtual void setToolbox(Toolbox* toolbox);

signals:
    void activeVehicleChanged(Vehicle* activeVehicle);

private:
    Vehicle* _activeVehicle;
};

#endif // VEHICLEMANAGER_H
