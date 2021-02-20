﻿#include "Vehicle.h"
#include "LinkManager.h"
#include "XApplication.h"
#include <QDebug>
#include <QSettings>

#define DEFINE_FACT(CLASS, NAME)                    \
    const char* CLASS::_##NAME##Fact##Name = #NAME; \
    Fact*       CLASS::NAME##Fact()                 \
    {                                               \
        return &_##NAME##Fact;                      \
    }

DEFINE_FACT(Vehicle, upperLimitLeftTrackHighSpeed)
DEFINE_FACT(Vehicle, upperLimitLeftTrackLowSpeed)
DEFINE_FACT(Vehicle, upperLimitLeftTrackFrettingSpeed)
DEFINE_FACT(Vehicle, lowerLimitLeftTrackSpeed)
DEFINE_FACT(Vehicle, upperLimitRightTrackHighSpeed)
DEFINE_FACT(Vehicle, upperLimitRightTrackLowSpeed)
DEFINE_FACT(Vehicle, upperLimitRightTrackFrettingSpeed)
DEFINE_FACT(Vehicle, lowerLimitRightTrackSpeed)
DEFINE_FACT(Vehicle, alarms)

const char* Vehicle::_teleRSSIFactName                    = "teleRSSI";
const char* Vehicle::_supplyVoltageFactName               = "supplyVoltage";
const char* Vehicle::_fuelLevelFactName                   = "fuelLevel";
const char* Vehicle::_rotatingSpeedFactName               = "rotatingSpeed";
const char* Vehicle::_waterTemperatureFactName            = "waterTemperature";
const char* Vehicle::_mainPumpPressureFactName            = "mainPumpPressure";
const char* Vehicle::_oxygenConcentrationFactName         = "oxygenConcentration";
const char* Vehicle::_combustibleGasConcentrationFactName = "combustibleGasConcentration";
const char* Vehicle::_ambientTemperaturenFactName         = "ambientTemperaturen";
const char* Vehicle::_xDegreeFactName                     = "xDegree";
const char* Vehicle::_yDegreeFactName                     = "yDegree";
const char* Vehicle::_workHoursFactName                   = "workHours";
const char* Vehicle::_oilTemperatureFactName              = "oilTemperature";
const char* Vehicle::_frontLightFactName                  = "frontLight";
const char* Vehicle::_backLightFactName                   = "backLight";
const char* Vehicle::_alarmLightFactName                  = "alarmLight";
const char* Vehicle::_poChaiLockFactName                  = "poChaiLock";
const char* Vehicle::_wajueLockFactName                   = "wajueLock";
const char* Vehicle::_poChaiQuickFactName                 = "poChaiQuick";
const char* Vehicle::_allSwitchsFactName                  = "allSwitchs";
//const char* Vehicle::_alarmsFactName                      = "alarms";

int Vehicle::testValue = 1; //测试用

Vehicle::Vehicle(QObject* parent)
    : FactGroup(_vehicleUIUpdateRateMSecs, ":/json/VehicleFact.json", parent)
    , _teleRSSIFact(_teleRSSIFactName, FactMetaData::valueTypeUint8)
    , _supplyVoltageFact(_supplyVoltageFactName, FactMetaData::valueTypeFloat)
    , _fuelLevelFact(_fuelLevelFactName, FactMetaData::valueTypeUint8)
    , _rotatingSpeedFact(_rotatingSpeedFactName, FactMetaData::valueTypeDouble)
    , _waterTemperatureFact(_waterTemperatureFactName, FactMetaData::valueTypeUint8)
    , _mainPumpPressureFact(_mainPumpPressureFactName, FactMetaData::valueTypeUint8)
    , _oxygenConcentrationFact(_oxygenConcentrationFactName, FactMetaData::valueTypeUint8)
    , _combustibleGasConcentrationFact(_combustibleGasConcentrationFactName, FactMetaData::valueTypeUint8)
    , _ambientTemperaturenFact(_ambientTemperaturenFactName, FactMetaData::valueTypeDouble)
    , _xDegreeFact(_xDegreeFactName, FactMetaData::valueTypeUint8)
    , _yDegreeFact(_yDegreeFactName, FactMetaData::valueTypeUint8)
    , _workHoursFact(_workHoursFactName, FactMetaData::valueTypeUint32)
    , _oilTemperatureFact(_oilTemperatureFactName, FactMetaData::valueTypeUint8)
    , _frontLightFact(_frontLightFactName, FactMetaData::valueTypeBool)
    , _backLightFact(_backLightFactName, FactMetaData::valueTypeBool)
    , _alarmLightFact(_alarmLightFactName, FactMetaData::valueTypeBool)
    , _poChaiLockFact(_poChaiLockFactName, FactMetaData::valueTypeBool)
    , _wajueLockFact(_wajueLockFactName, FactMetaData::valueTypeBool)
    , _poChaiQuickFact(_poChaiQuickFactName, FactMetaData::valueTypeBool)
    , _allSwitchsFact(_allSwitchsFactName, FactMetaData::valueTypeInt8)
    , _upperLimitLeftTrackHighSpeedFact(_upperLimitLeftTrackHighSpeedFactName, FactMetaData::valueTypeUint8)
    , _upperLimitLeftTrackLowSpeedFact(_upperLimitLeftTrackLowSpeedFactName, FactMetaData::valueTypeUint8)
    , _upperLimitLeftTrackFrettingSpeedFact(_upperLimitLeftTrackFrettingSpeedFactName, FactMetaData::valueTypeUint8)
    , _lowerLimitLeftTrackSpeedFact(_lowerLimitLeftTrackSpeedFactName, FactMetaData::valueTypeUint8)
    , _upperLimitRightTrackHighSpeedFact(_upperLimitRightTrackHighSpeedFactName, FactMetaData::valueTypeUint8)
    , _upperLimitRightTrackLowSpeedFact(_upperLimitRightTrackLowSpeedFactName, FactMetaData::valueTypeUint8)
    , _upperLimitRightTrackFrettingSpeedFact(_upperLimitRightTrackFrettingSpeedFactName, FactMetaData::valueTypeUint8)
    , _lowerLimitRightTrackSpeedFact(_lowerLimitRightTrackSpeedFactName, FactMetaData::valueTypeUint8)
    , _alarmsFact(_alarmsFactName, FactMetaData::valueTypeInt8)
{
    _commonInit();
}

void Vehicle::_commonInit()
{
    _addFact(&_teleRSSIFact, _teleRSSIFactName);
    _addFact(&_supplyVoltageFact, _supplyVoltageFactName);
    _addFact(&_fuelLevelFact, _fuelLevelFactName);
    _addFact(&_rotatingSpeedFact, _rotatingSpeedFactName);
    _addFact(&_waterTemperatureFact, _waterTemperatureFactName);
    _addFact(&_mainPumpPressureFact, _mainPumpPressureFactName);
    _addFact(&_oxygenConcentrationFact, _oxygenConcentrationFactName);
    _addFact(&_combustibleGasConcentrationFact, _combustibleGasConcentrationFactName);
    _addFact(&_ambientTemperaturenFact, _ambientTemperaturenFactName);
    _addFact(&_xDegreeFact, _xDegreeFactName);
    _addFact(&_yDegreeFact, _yDegreeFactName);
    _addFact(&_workHoursFact, _workHoursFactName);
    _addFact(&_oilTemperatureFact, _oilTemperatureFactName);

    _addFact(&_frontLightFact, _frontLightFactName);
    _addFact(&_backLightFact, _backLightFactName);
    _addFact(&_alarmLightFact, _alarmLightFactName);
    _addFact(&_poChaiLockFact, _poChaiLockFactName);
    _addFact(&_wajueLockFact, _wajueLockFactName);
    _addFact(&_poChaiQuickFact, _poChaiQuickFactName);
    _addFact(&_allSwitchsFact, _allSwitchsFactName);
    _addFact(&_upperLimitLeftTrackHighSpeedFact, _upperLimitLeftTrackHighSpeedFactName);
    _addFact(&_upperLimitLeftTrackLowSpeedFact, _upperLimitLeftTrackLowSpeedFactName);
    _addFact(&_upperLimitLeftTrackFrettingSpeedFact, _upperLimitLeftTrackFrettingSpeedFactName);
    _addFact(&_lowerLimitLeftTrackSpeedFact, _lowerLimitLeftTrackSpeedFactName);
    _addFact(&_upperLimitRightTrackHighSpeedFact, _upperLimitRightTrackHighSpeedFactName);
    _addFact(&_upperLimitRightTrackLowSpeedFact, _upperLimitRightTrackLowSpeedFactName);
    _addFact(&_upperLimitRightTrackFrettingSpeedFact, _upperLimitRightTrackFrettingSpeedFactName);
    _addFact(&_lowerLimitRightTrackSpeedFact, _lowerLimitRightTrackSpeedFactName);
    _addFact(&_alarmsFact, _alarmsFactName);

    cl = XApp()->toolbox()->linkManager()->canlink();
}

void Vehicle::forceArm()
{
    qDebug() << "forceArm-------";
}

void Vehicle::sendFrontLightSwitch(bool b)
{
    const uint frameId = 0X1801F01;
    _switch[ 0 ]       = b;
    frontLightFact()->setRawValue(b);
    QCanBusFrame frame = QCanBusFrame(frameId, _switch);
    cl->writeCanFrame(frame);
    qDebug() << _switch;
}

void Vehicle::sendBackLightSwitch(bool b)
{
    const uint frameId = 0X1801F01;
    _switch[ 1 ]       = b;
    QCanBusFrame frame = QCanBusFrame(frameId, _switch);
    cl->writeCanFrame(frame);
    qDebug() << _switch;
}

void Vehicle::sendAlarmSwitch(bool b)
{
    const uint frameId = 0x1801F01;
    _switch[ 2 ]       = b;
    QCanBusFrame frame = QCanBusFrame(frameId, _switch);
    cl->writeCanFrame(frame);
    qDebug() << _switch;
}

void Vehicle::sendPoChaiLockSwitch(bool b)
{
    const uint frameId = 0x1801F01;
    _switch[ 3 ]       = b;
    QCanBusFrame frame = QCanBusFrame(frameId, _switch);
    cl->writeCanFrame(frame);
    qDebug() << _switch;
}

void Vehicle::sendWajueLockSwitch(bool b)
{
    const uint frameId = 0x1801F01;
    _switch[ 4 ]       = b;
    QCanBusFrame frame = QCanBusFrame(frameId, _switch);
    cl->writeCanFrame(frame);
    qDebug() << _switch;
}

void Vehicle::sendPoChaiQuickSwitch(bool b)
{
    const uint frameId = 0x1801F01;
    _switch[ 5 ]       = b;
    QCanBusFrame frame = QCanBusFrame(frameId, _switch);
    cl->writeCanFrame(frame);
    qDebug() << _switch;
}

void Vehicle::sendReadControl(bool b)
{
    const uint frameId = 0x1801F01;
    _switch[ 6 ]       = b;
    QCanBusFrame frame = QCanBusFrame(frameId, _switch);
    cl->writeCanFrame(frame);
    qDebug() << _switch;

}

void Vehicle::sendWriteControl(bool b)
{
    const uint frameId = 0x1801F01;
    _switch[ 7 ]       = b;
    QCanBusFrame frame = QCanBusFrame(frameId, _switch);
    cl->writeCanFrame(frame);
        qDebug() << _switch;
}

void Vehicle::updateAllParams()
{
        const uint frameId = 0x01801F0C;
        QByteArray b;
        b[0] = upperLimitLeftTrackHighSpeedFact()->cookedValue().toUInt();
        b[1] = upperLimitLeftTrackLowSpeedFact()->cookedValue().toUInt();
        b[2] = upperLimitLeftTrackFrettingSpeedFact()->cookedValue().toUInt();
        b[3] = lowerLimitLeftTrackSpeedFact()->cookedValue().toUInt();
        b[4] = upperLimitRightTrackHighSpeedFact()->cookedValue().toUInt();
        b[5] = upperLimitRightTrackLowSpeedFact()->cookedValue().toUInt();
        b[6] = upperLimitRightTrackFrettingSpeedFact()->cookedValue().toUInt();
        b[7] = lowerLimitRightTrackSpeedFact()->cookedValue().toUInt();
        QCanBusFrame frame = QCanBusFrame(frameId, b);
        cl->writeCanFrame(frame);
            qDebug() << b.toHex(':');
}

void Vehicle::_updateAllValues()
{
    //qDebug() << "updateAllValues ";
    FactGroup::_updateAllValues();
}
