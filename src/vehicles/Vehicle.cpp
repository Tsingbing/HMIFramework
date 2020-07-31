#include "Vehicle.h"
#include <QSettings>

const char* Vehicle::_carSpeedFactName          = "carSpeed";
const char* Vehicle::_rotatingSpeedFactName     = "rotatingSpeed";
const char* Vehicle::_oilPressureFactName       = "oilPressure";
const char* Vehicle::_waterTemperatureFactName  = "waterTemperature";
const char* Vehicle::_airPressureFactName       = "airPressure";

int Vehicle::testValue = 1; //测试用

Vehicle::Vehicle(QObject *parent)
    : FactGroup(_vehicleUIUpdateRateMSecs, ":/json/VehicleFact.json", parent)
{
    _addFact(&_carSpeedFact,           _carSpeedFactName);
    _addFact(&_rotatingSpeedFact,   _rotatingSpeedFactName);
    _setupTimer();
}

void Vehicle::_updateValue()
{
    ///< 测试：变化的速度值
    /// 在ui获取fact值
    /// 例如 connect(ve->carSpeedFact(),&Fact::valueChanged,this,&Dialog::_carUpdated);
    if(testValue++ > 10000)
        testValue = 0;
    _carSpeedFact.setRawValue(QVariant(testValue));
}

void Vehicle::_setupTimer()
{
    connect(&_updateTime, &QTimer::timeout, this, &Vehicle::_updateValue);
    _updateTime.setSingleShot(false);
    _updateTime.setInterval(10);
    _updateTime.start();
}
