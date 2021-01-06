#include "Vehicle.h"
#include "LinkManager.h"
#include "XApplication.h"
#include <QDebug>
#include <QSettings>

const char* Vehicle::_carSpeedFactName    = "carSpeed";
const char* Vehicle::_oilPressureFactName = "oilPressure";
const char* Vehicle::_airPressureFactName = "airPressure";

const char* Vehicle::_teleRSSIFactName                    = "teleRSSI";
const char* Vehicle::_supplyVoltageFactName               = "supplyVoltage";
const char* Vehicle::_fuelLevelFactName                   = "fuelLevel";
const char* Vehicle::_rotatingSpeedFactName               = "rotatingSpeed";
const char* Vehicle::_waterTemperatureFactName            = "oilPressure";
const char* Vehicle::_mainPumpPressureFactName            = "mainPumpPressure";
const char* Vehicle::_oxygenConcentrationFactName         = "oxygenConcentration";
const char* Vehicle::_combustibleGasConcentrationFactName = "combustibleGasConcentration";
const char* Vehicle::_AmbientTemperaturenFactName         = "AmbientTemperaturen";
const char* Vehicle::_XDegreeFactName                     = "XDegree";
const char* Vehicle::_YDegreeFactName                     = "YDegree";
const char* Vehicle::_workHoursFactName                   = "workHours";

int Vehicle::testValue = 1; //测试用

Vehicle::Vehicle(QObject* parent)
    : FactGroup(_vehicleUIUpdateRateMSecs, ":/json/VehicleFact.json", parent)
    , _supplyVoltageFact(_supplyVoltageFactName, FactMetaData::valueTypeFloat)
{
    _addFact(&_carSpeedFact, _carSpeedFactName);
    _addFact(&_teleRSSIFact, _teleRSSIFactName);
    _addFact(&_supplyVoltageFact, _supplyVoltageFactName);
    _addFact(&_fuelLevelFact, _fuelLevelFactName);
    _addFact(&_rotatingSpeedFact, _rotatingSpeedFactName);
    _addFact(&_waterTemperatureFact, _waterTemperatureFactName);
    _addFact(&_mainPumpPressureFact, _mainPumpPressureFactName);
    _addFact(&_oxygenConcentrationFact, _oxygenConcentrationFactName);
    _addFact(&_combustibleGasConcentrationFact, _combustibleGasConcentrationFactName);
    _addFact(&_AmbientTemperaturenFact, _AmbientTemperaturenFactName);
    _addFact(&_XDegreeFact, _XDegreeFactName);
    _addFact(&_YDegreeFact, _YDegreeFactName);
    _addFact(&_workHoursFact, _workHoursFactName);

    cl = XApp()->toolbox()->linkManager()->canlink();
}

void Vehicle::forceArm()
{
    qDebug() << "forceArm-------";
}

void Vehicle::sendFrontLightSwitch(bool b)
{
    const uint       frameId = 2;
    QString          data    = "00 01 02 03 04 05 00 07";
    const QByteArray payload = QByteArray::fromHex(data.remove(QLatin1Char(' ')).toLatin1());

    QCanBusFrame frame = QCanBusFrame(frameId, payload);
    cl->writeCanFrame(frame);
}

void Vehicle::sendBackLightSwitch(bool b)
{
    const uint       frameId = 3;
    QString          data    = "00 01 02 03 04 05 00 07";
    const QByteArray payload = QByteArray::fromHex(data.remove(QLatin1Char(' ')).toLatin1());

    QCanBusFrame frame = QCanBusFrame(frameId, payload);
    cl->writeCanFrame(frame);
}

void Vehicle::sendAlarmSwitch(bool b)
{
    const uint       frameId = 4;
    QString          data    = "00 01 02 03 04 05 00 07";
    const QByteArray payload = QByteArray::fromHex(data.remove(QLatin1Char(' ')).toLatin1());

    QCanBusFrame frame = QCanBusFrame(frameId, payload);
    cl->writeCanFrame(frame);
}

void Vehicle::sendPoChaiLockSwitch(bool b)
{
    const uint       frameId = 5;
    QString          data    = "00 01 02 03 04 05 00 07";
    const QByteArray payload = QByteArray::fromHex(data.remove(QLatin1Char(' ')).toLatin1());

    QCanBusFrame frame = QCanBusFrame(frameId, payload);
    cl->writeCanFrame(frame);
}

void Vehicle::sendWajueLockSwitch(bool b)
{
    const uint       frameId = 6;
    QString          data    = "00 01 02 03 04 05 00 07";
    const QByteArray payload = QByteArray::fromHex(data.remove(QLatin1Char(' ')).toLatin1());

    QCanBusFrame frame = QCanBusFrame(frameId, payload);
    cl->writeCanFrame(frame);
}

void Vehicle::sendPoChaiQuickSwitch(bool b)
{
    const uint       frameId = 7;
    QString          data    = "00 01 02 03 04 05 00 07";
    const QByteArray payload = QByteArray::fromHex(data.remove(QLatin1Char(' ')).toLatin1());

    QCanBusFrame frame = QCanBusFrame(frameId, payload);
    cl->writeCanFrame(frame);
}

void Vehicle::_updateAllValues()
{
    //qDebug() << "updateAllValues ";
    FactGroup::_updateAllValues();
}
