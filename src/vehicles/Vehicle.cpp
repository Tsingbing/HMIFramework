#include "XApplication.h"
#include "Vehicle.h"
#include "LinkManager.h"
#include <QSettings>
#include <QDebug>
#include <QProcess>

const char * Vehicle::_carSpeedFactName          = "carSpeed";
const char * Vehicle::_oilPressureFactName       = "oilPressure";
const char * Vehicle::_airPressureFactName       = "airPressure";
const char * Vehicle::_teleRSSIFactName         = "teleRSSI";
const char * Vehicle::_supplyVoltageFactName    = "supplyVoltage";
const char * Vehicle::_fuelLevelFactName        = "fuelLevel";
const char * Vehicle::_rotatingSpeedFactName     = "rotatingSpeed";
const char * Vehicle::_waterTemperatureFactName  = "waterTemperature";
const char * Vehicle::_oilTemperatureFactName   = "oilTemperature";
const char * Vehicle::_mainPumpPressureFactName  = "mainPumpPressure";
const char * Vehicle::_frontPumpPressureFactName  = "frontPumpPressure";
const char * Vehicle::_backPumpPressureFactName  = "backPumpPressure";
const char * Vehicle::_oxygenConcentrationFactName = "oxygenConcentration";
const char * Vehicle::_combustibleGasConcentrationFactName = "combustibleGasConcentration";
const char * Vehicle::_AmbientTemperaturenFactName = "AmbientTemperaturen";
const char * Vehicle::_XDegreeFactName          = "XDegree";
const char * Vehicle::_YDegreeFactName          = "YDegree";
const char * Vehicle::_workHoursFactName        = "workHours";

int Vehicle::testValue = 1; //测试用

Vehicle::Vehicle(QObject *parent)
    : FactGroup(_vehicleUIUpdateRateMSecs, ":/json/VehicleFact.json", parent)
{
    _warningEnum << "数据正常"<<"下限报警" << "下限预报警" << "上限预报警" << "上限报警" << "传感器开路" << "传感器短路" << "其他异常" ;
    _addFact(&_carSpeedFact,            _carSpeedFactName);
    _addFact(&_teleRSSIFact,            _teleRSSIFactName);
    _addFact(&_supplyVoltageFact,       _supplyVoltageFactName);
    _addFact(&_fuelLevelFact,           _fuelLevelFactName);
    _addFact(&_rotatingSpeedFact,       _rotatingSpeedFactName);
    _addFact(&_waterTemperatureFact,    _waterTemperatureFactName);
    _addFact(&_oilTemperatureFact,      _oilTemperatureFactName);
    _addFact(&_mainPumpPressureFact,    _mainPumpPressureFactName);
    _addFact(&_frontPumpPressureFact,    _frontPumpPressureFactName);
    _addFact(&_backPumpPressureFact,    _backPumpPressureFactName);
    _addFact(&_oxygenConcentrationFact, _oxygenConcentrationFactName);
    _addFact(&_combustibleGasConcentrationFact,_combustibleGasConcentrationFactName);
    _addFact(&_AmbientTemperaturenFact,         _AmbientTemperaturenFactName);
    _addFact(&_XDegreeFact,             _XDegreeFactName);
    _addFact(&_YDegreeFact,             _YDegreeFactName);
    _addFact(&_workHoursFact,           _workHoursFactName);

    cl = XApp()->toolbox()->linkManager()->canlink();
}

void Vehicle::_updateAllValues()
{
    //qDebug() << "updateAllValues ";
    warningList.clear();
    warningList.insert(0,"电源电压"+_warningEnum.at(dianyaWarning < 7 ? dianyaWarning : 7 ));
    warningList.insert(1,"冷却水温"+_warningEnum.at(shuiwenWarning < 7 ? shuiwenWarning : 7 ));
    warningList.insert(2,"发动机转速"+_warningEnum.at(zhuansuWarning < 7 ? zhuansuWarning : 7 ));
    warningList.insert(3,"燃油量"+_warningEnum.at(ranyouWarning < 7 ? ranyouWarning : 7 ));
    warningList.insert(4,"液压油温"+_warningEnum.at(youwenWarning < 7 ? youwenWarning : 7 ));
    warningList.insert(5,"前泵压力"+_warningEnum.at(qianbengWarning < 7 ? qianbengWarning : 7 ));
    warningList.insert(6,"后泵压力"+_warningEnum.at(houbengWarning < 7 ? houbengWarning : 7 ));

    bool XBaojing = false;
    bool YBaojing = false;
    //报警
    if(XDegreeFact()->value().toInt() > 15 || XDegreeFact()->value().toInt() < -15)
    {
        XBaojing = true;
        warningList.insert(7,"X倾角过大");
    }
    else
    {
        XBaojing = false;
        warningList.insert(7,"X倾角数据正常");
    }

    //报警
    if(YDegreeFact()->value().toInt() > 25 || YDegreeFact()->value().toInt() < -25) {
        YBaojing = true;
        warningList.insert(8,"Y倾角过大");
    }
    else {
        YBaojing = false;
        warningList.insert(8,"Y倾角数据正常");
    }

    if(XBaojing || YBaojing) { //蜂鸣器报警
        QProcess::execute("/bin/sh -c \"echo 500 > /sys/class/misc/pwmbuzzer/pwmbuzzer/buzzer\"");
    }
    else {
        QProcess::execute("/bin/sh -c \"echo 0 > /sys/class/misc/pwmbuzzer/pwmbuzzer/buzzer\"");
    }

    qDebug() <<warningList;

    QStringList list;
    for(int index=0; index<warningList.size();index++)
    {
        if(!warningList.at(index).contains("数据正常"))
            list.append(warningList.at(index));
    }

    qDebug() <<list;
    warningList = list;
    FactGroup::_updateAllValues();

}
