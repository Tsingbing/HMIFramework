#ifndef TOOLBOX_H
#define TOOLBOX_H

#include <QObject>

class VehicleManager;
class LinkManager;

class Toolbox : public QObject
{
    Q_OBJECT
public:
    Toolbox(QObject *parent = nullptr);

    VehicleManager* vehicleManager() {return _vehicleManager;}
    LinkManager* linkManager() {return _linkManager;}

signals:

private:
    void setChildToolboxes();

    VehicleManager* _vehicleManager = nullptr;
    LinkManager*     _linkManager   = nullptr;
    friend class XApplication;
};

#endif // TOOLBOX_H
