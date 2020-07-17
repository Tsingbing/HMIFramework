#ifndef TOOLBOX_H
#define TOOLBOX_H

#include <QObject>

class VehicleManager;

///< 它用于管理我们所有的顶级服务/工具
class Toolbox : public QObject
{
    Q_OBJECT
public:
    Toolbox(QObject *parent = nullptr);

    VehicleManager* vehicleManager() {return _vehicleManager;}

signals:

private:
    void setChildToolboxes();

    VehicleManager* _vehicleManager = nullptr;

    friend class XApplication;
};

#endif // TOOLBOX_H
