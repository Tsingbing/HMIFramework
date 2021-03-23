#ifndef TOOLBOX_H
#define TOOLBOX_H

#include <QObject>

class FactSystem;
class XApplication;
class VehicleManager;
class LinkManager;
class CanLinkProtocol;
class SettingsManager;
class VideoManager;

class Toolbox : public QObject
{
    Q_OBJECT
public:
    Toolbox(XApplication* app);

    VehicleManager* vehicleManager()
    {
        return _vehicleManager;
    }
    LinkManager* linkManager()
    {
        return _linkManager;
    }
    CanLinkProtocol* canLinkProtocol()
    {
        return _canLinkProtocol;
    }

    SettingsManager* settingsManager()
    {
        return _settingsManager;
    }

    VideoManager* videoManager()
    {
        return _videoManager;
    }
signals:

private:
    void setChildToolboxes();

    FactSystem*      _factSystem      = nullptr;
    VehicleManager*  _vehicleManager  = nullptr;
    LinkManager*     _linkManager     = nullptr;
    CanLinkProtocol* _canLinkProtocol = nullptr;
    SettingsManager* _settingsManager = nullptr;
    VideoManager*    _videoManager    = nullptr;

    friend class XApplication;
};

#endif // TOOLBOX_H
