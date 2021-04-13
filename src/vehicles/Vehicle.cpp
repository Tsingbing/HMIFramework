#include "Vehicle.h"
#include "LinkManager.h"
#include "XApplication.h"
#include <QDebug>
#include <QSettings>
#include <QThread>
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
DEFINE_FACT(Vehicle, batteryPower)
DEFINE_FACT(Vehicle, upperLimitLeftTrackBackHighSpeed)
DEFINE_FACT(Vehicle, upperLimitLeftTrackBackLowSpeed)
DEFINE_FACT(Vehicle, upperLimitRightTrackBackHighSpeed)
DEFINE_FACT(Vehicle, upperLimitRightTrackBackLowSpeed)


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
const char* Vehicle::_engineFactGroupName = "engine";


int Vehicle::testValue = 1; //测试用
DEFINE_FACT(EngineFactGroup, pochaiIsLock)
DEFINE_FACT(EngineFactGroup, wajueIsLock)

const char* EngineFactGroup::_rotatingSpeedFactName = "rotatingSpeed";
const char* EngineFactGroup::_xDegreeFactName = "xDegree";
const char* EngineFactGroup::_yDegreeFactName = "yDegree";

EngineFactGroup::EngineFactGroup(QObject* parent)
    : FactGroup(500, ":/json/EngineFact.json", parent)
    , _rotatingSpeedFact(_rotatingSpeedFactName, FactMetaData::valueTypeUint32)
    , _xDegreeFact(_xDegreeFactName, FactMetaData::valueTypeFloat)
    , _yDegreeFact(_yDegreeFactName, FactMetaData::valueTypeFloat)
    , _pochaiIsLockFact(_pochaiIsLockFactName, FactMetaData::valueTypeBool)
    , _wajueIsLockFact(_wajueIsLockFactName, FactMetaData::valueTypeBool)
{
    _addFact(&_rotatingSpeedFact, _rotatingSpeedFactName);
    _addFact(&_xDegreeFact, _xDegreeFactName);
    _addFact(&_yDegreeFact, _yDegreeFactName);
    _addFact(&_pochaiIsLockFact, _pochaiIsLockFactName);
    _addFact(&_wajueIsLockFact, _wajueIsLockFactName);

    _xDegreeFact.setRawValue          (std::numeric_limits<float>::quiet_NaN());
    _yDegreeFact.setRawValue  (std::numeric_limits<float>::quiet_NaN());
}

void EngineFactGroup::_updateAllValues()
{
    FactGroup::_updateAllValues();

//    if(_pochaiIsLockFact->cookedValue)
//        _warningsStringsQMap.insert(_pochaiIsLockFact->shortDescription(),_pochaiIsLockFact->shortDescription());
//    else
//        _warningsStringsQMap.remove(_pochaiIsLockFact->shortDescription());

//    if(_wajueIsLockFact->cookedValue)
//        _warningsStringsQMap.insert(_wajueIsLockFact->shortDescription(),_wajueIsLockFact->shortDescription());
//    else
//        _warningsStringsQMap.remove(_wajueIsLockFact->shortDescription());

//    _warningsStrings = _warningsStringsQMap.values();
}

Vehicle::Vehicle(QObject* parent)
    : FactGroup(1000, ":/json/VehicleFact.json", parent)
    , _teleRSSIFact(_teleRSSIFactName, FactMetaData::valueTypeUint8)
    , _supplyVoltageFact(_supplyVoltageFactName, FactMetaData::valueTypeFloat)
    , _fuelLevelFact(_fuelLevelFactName, FactMetaData::valueTypeUint8)
    , _rotatingSpeedFact(_rotatingSpeedFactName, FactMetaData::valueTypeDouble)
    , _waterTemperatureFact(_waterTemperatureFactName, FactMetaData::valueTypeUint8)
    , _mainPumpPressureFact(_mainPumpPressureFactName, FactMetaData::valueTypeUint8)
    , _oxygenConcentrationFact(_oxygenConcentrationFactName, FactMetaData::valueTypeUint8)
    , _combustibleGasConcentrationFact(_combustibleGasConcentrationFactName, FactMetaData::valueTypeUint8)
    , _ambientTemperaturenFact(_ambientTemperaturenFactName, FactMetaData::valueTypeDouble)
    , _xDegreeFact(_xDegreeFactName, FactMetaData::valueTypeFloat)
    , _yDegreeFact(_yDegreeFactName, FactMetaData::valueTypeFloat)
    , _workHoursFact(_workHoursFactName, FactMetaData::valueTypeDouble)
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
    , _upperLimitLeftTrackBackHighSpeedFact(_upperLimitLeftTrackBackHighSpeedFactName, FactMetaData::valueTypeUint8)
    , _upperLimitLeftTrackBackLowSpeedFact(_upperLimitLeftTrackBackLowSpeedFactName, FactMetaData::valueTypeUint8)
    , _upperLimitRightTrackBackHighSpeedFact(_upperLimitRightTrackBackHighSpeedFactName, FactMetaData::valueTypeUint8)
    , _upperLimitRightTrackBackLowSpeedFact(_upperLimitRightTrackBackLowSpeedFactName, FactMetaData::valueTypeUint8)
    , _alarmsFact(_alarmsFactName, FactMetaData::valueTypeInt8)
    , _batteryPowerFact(_batteryPowerFactName, FactMetaData::valueTypeUint8)
    , _engineFactGroup(this)
{
    _commonInit();
    connect(cl, &CanLink::canframesRecived, this, &Vehicle::_canframesRecived);
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

    _addFact(&_upperLimitLeftTrackBackHighSpeedFact, _upperLimitLeftTrackBackHighSpeedFactName);
    _addFact(&_upperLimitLeftTrackBackLowSpeedFact, _upperLimitLeftTrackBackLowSpeedFactName);
    _addFact(&_upperLimitRightTrackBackHighSpeedFact, _upperLimitRightTrackBackHighSpeedFactName);
    _addFact(&_upperLimitRightTrackBackLowSpeedFact, _upperLimitRightTrackBackLowSpeedFactName);

    _addFact(&_alarmsFact, _alarmsFactName);
    _addFact(&_batteryPowerFact, _batteryPowerFactName);
    _addFactGroup(&_engineFactGroup, _engineFactGroupName);

    _supplyVoltageFact.setRawValue          (std::numeric_limits<float>::quiet_NaN());
    _workHoursFact.setRawValue  (std::numeric_limits<float>::quiet_NaN());
    _ambientTemperaturenFact.setRawValue  (std::numeric_limits<float>::quiet_NaN());
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

void Vehicle::sendPoChaiLockSwitch(int b)
{
    const uint frameId = 0x1801F01;
    _switch[ 3 ]       = b;
    QCanBusFrame frame = QCanBusFrame(frameId, _switch);
    cl->writeCanFrame(frame);
    qDebug() << _switch;
}

void Vehicle::sendWajueLockSwitch(int b)
{
    const uint frameId = 0x1801F01;
    _switch[ 4 ]       = b;
    QCanBusFrame frame = QCanBusFrame(frameId, _switch);
    cl->writeCanFrame(frame);
    qDebug() << _switch;
}

void Vehicle::sendPoChaiQuickSwitch(int b)
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

void Vehicle::sendJiesuo(bool b)
{
    const uint frameId = 0xcf00201;
    QByteArray _byteArray;
    _byteArray[ 0 ]       = 0x2f;
    _byteArray[ 1 ]       = 0x00;
    _byteArray[ 2 ]       = 0x20;
    _byteArray[ 3 ]       = 0x01;
    _byteArray[ 4 ]       = b;
    _byteArray[ 5 ]       = 0;
    _byteArray[ 6 ]       = 0;
    _byteArray[ 7 ]       = 0;
    QCanBusFrame frame = QCanBusFrame(frameId, _byteArray);
    cl->writeCanFrame(frame);
    qDebug() << _byteArray;
//    static int i = 0;
//    i++;
//    _warningsStrings.append(QString::number(i));
//    if(i == 5)
//        _warningsStrings.clear();
//    _engineFactGroup.pochaiIsLockFact()->setRawValue(QVariant(b));
//    _engineFactGroup.wajueIsLockFact()->setRawValue(QVariant(b));
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

    QThread::msleep(100);
    //add
    const uint frameIdb = 0X1801F0D;
    QByteArray bb;
    bb[0] = upperLimitLeftTrackBackHighSpeedFact()->cookedValue().toUInt();
    bb[1] = upperLimitLeftTrackBackLowSpeedFact()->cookedValue().toUInt();
    bb[2] = upperLimitRightTrackBackHighSpeedFact()->cookedValue().toUInt();
    bb[3] = upperLimitRightTrackBackLowSpeedFact()->cookedValue().toUInt();
    bb[4] = 0;
    bb[5] = 0;
    bb[6] = 0;
    bb[7] = 0;
    QCanBusFrame frameb = QCanBusFrame(frameIdb, bb);
    cl->writeCanFrame(frameb);
        qDebug() << bb.toHex(':');

    QThread::msleep(100);
    //发送写命令
    sendWriteControl(1);

    QThread::msleep(100);
    //发送读命令
    sendReadControl(1);
}

void Vehicle::_updateAllValues()
{
    //qDebug() << "updateAllValues ";
    FactGroup::_updateAllValues();
    /*
    if(_engineFactGroup.pochaiIsLockFact()->cookedValue().toBool())
        _warningsStringsQMap.insert(_engineFactGroup.pochaiIsLockFact()->shortDescription(),_engineFactGroup.pochaiIsLockFact()->shortDescription());
    else
        _warningsStringsQMap.remove(_engineFactGroup.pochaiIsLockFact()->shortDescription());

    if(_engineFactGroup.pochaiIsLockFact()->cookedValue().toBool())
        _warningsStringsQMap.insert(_engineFactGroup.wajueIsLockFact()->shortDescription(),_engineFactGroup.wajueIsLockFact()->shortDescription());
    else
        _warningsStringsQMap.remove(_engineFactGroup.wajueIsLockFact()->shortDescription());
    */
    _warningsStringsQMap.clear();
    for (int i = 0; i < 7; i++) {
      if((_alarmsFact.cookedValue().toUInt() >> i) & 0x01)
          _warningsStringsQMap.insert(_alarmsFact.bitmaskStrings().at(i),_alarmsFact.bitmaskStrings().at(i));
      else
          _warningsStringsQMap.remove(_alarmsFact.bitmaskStrings().at(i));
    }

    _warningsStrings = _warningsStringsQMap.values();
}

void Vehicle::_canframesRecived(QCanBusFrame canbusframe)
{
    QString view;

    view = canbusframe.toString();

    const QString time = QString::fromLatin1("%1.%2  ")
                             .arg(canbusframe.timeStamp().seconds(), 10, 10, QLatin1Char(' '))
                             .arg(canbusframe.timeStamp().microSeconds() / 100, 3, 10, QLatin1Char('0'));

    qCDebug(CanLog) << time << view;

    quint32    frameId = canbusframe.frameId();
    QByteArray payload = canbusframe.payload();

    switch (frameId)
    {
        case 0x0CF00381:
        {
            batteryPowerFact()->setRawValue(QVariant(payload.at(1)));
        }
        break;
        case 0x01801F09:
        {
            //qDebug() << "payload 0x10F51001: " << payload.toHex(':');
            //系统电压
            supplyVoltageFact()->setRawValue(QVariant((payload.at(0) + (payload.at(1) << 8)) * 0.1));
            fuelLevelFact()->setRawValue(QVariant(payload.at(2)));
            oxygenConcentrationFact()->setRawValue(QVariant(payload.at(3)));
            mainPumpPressureFact()->setRawValue(QVariant((payload.at(4) + (payload.at(5) << 8)) * 0.1));
            combustibleGasConcentrationFact()->setRawValue(QVariant(payload.at(6)));
            ambientTemperaturenFact()->setRawValue(QVariant(payload.at(7) - 20));
        }
        break;
        case 0x18ECFF1C:
        {
            _alarmsFact.setRawValue(QVariant(payload.at(0)));
            _engineFactGroup.yDegreeFact()->setRawValue(QVariant((payload.at(1) + (payload.at(2) << 8) - 9000) * 0.01));
            _engineFactGroup.xDegreeFact()->setRawValue(QVariant((payload.at(3) + (payload.at(4) << 8) - 9000) * 0.01));
            _engineFactGroup.rotatingSpeedFact()->setRawValue(QVariant((payload.at(5) + (payload.at(6) << 8)) * 0.125));
            _waterTemperatureFact.setRawValue(QVariant(payload.at(7) - 40));
        }
        break;
        case 0x1CEBFF1C:
        {
            _workHoursFact.setRawValue(QVariant(
                (payload.at(0) + (payload.at(1) << 8) + (payload.at(2) << 16) + (payload.at(3) << 24)) * 0.05));
            _oilTemperatureFact.setRawValue(QVariant(payload.at(4)));
            _engineFactGroup.pochaiIsLockFact()->setRawValue(QVariant((payload.at(5)) & 0x01));
            _engineFactGroup.wajueIsLockFact()->setRawValue(QVariant((payload.at(5)) & 0x02));

        }
        break;
        case 0x18EDFF1C:
        {
            _upperLimitLeftTrackHighSpeedFact.setRawValue(QVariant(payload.at(0)));
            _upperLimitLeftTrackLowSpeedFact.setRawValue(QVariant(payload.at(1)));
            _upperLimitLeftTrackFrettingSpeedFact.setRawValue(QVariant(payload.at(2)));
            _lowerLimitLeftTrackSpeedFact.setRawValue(QVariant(payload.at(3)));
            _upperLimitRightTrackHighSpeedFact.setRawValue(QVariant(payload.at(4)));
            _upperLimitRightTrackLowSpeedFact.setRawValue(QVariant(payload.at(5)));
            _upperLimitRightTrackFrettingSpeedFact.setRawValue(QVariant(payload.at(6)));
            _lowerLimitRightTrackSpeedFact.setRawValue(QVariant(payload.at(7)));
        }
        break;
        case 0x18EEFF1C:
        {
            _upperLimitLeftTrackBackHighSpeedFact.setRawValue(QVariant(payload.at(0)));
            _upperLimitLeftTrackBackLowSpeedFact.setRawValue(QVariant(payload.at(1)));
            _upperLimitRightTrackBackHighSpeedFact.setRawValue(QVariant(payload.at(2)));
            _upperLimitRightTrackBackLowSpeedFact.setRawValue(QVariant(payload.at(3)));
        }
        break;
    }
}
