#ifndef TOOLBOX_H
#define TOOLBOX_H

#include <QObject>

class VehicleManager;

class Toolbox : public QObject
{
    Q_OBJECT
public:
    Toolbox(QObject *parent = 0);

    VehicleManager* vehicleManager() {return _vehicleManager;}

signals:

private:
    void setChildToolboxes();

    VehicleManager* _vehicleManager = 0;

    friend class XApplication;
};

#endif // TOOLBOX_H
