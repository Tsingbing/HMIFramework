#ifndef TOOLBOX_H
#define TOOLBOX_H

#include <QObject>

class XApplication;
class VehicleManager;
class LinkManager;
class CanLinkProtocol;

class Toolbox : public QObject
{
    Q_OBJECT
public:
    Toolbox(XApplication *app);

    VehicleManager* vehicleManager() {return _vehicleManager;}
    LinkManager* linkManager() {return _linkManager;}
    CanLinkProtocol *canLinkProtocol() {return _canLinkProtocol;}

signals:

private:
    void setChildToolboxes();

    VehicleManager* _vehicleManager = nullptr;
    LinkManager*     _linkManager   = nullptr;
    CanLinkProtocol* _canLinkProtocol = nullptr;
    friend class XApplication;
};

#endif // TOOLBOX_H
