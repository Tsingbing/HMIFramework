#ifndef VEHICLE_H
#define VEHICLE_H

#include <QObject>
#include "Toolbox.h"
#include "FactGroup.h"
#include <QCanBusFrame>

class CanLink;

class Vehicle : public FactGroup
{
    Q_OBJECT
public:
    Vehicle(QObject *parent = nullptr);

    Fact *carSpeedFact() { return &_carSpeedFact; }
    Fact *oilPressureFact() { return &_oilPressureFact; }
    Fact *airPressureFact() { return &_airPressureFact; }

    Fact *teleRSSIFact() { return &_teleRSSIFact; }
    Fact *supplyVoltageFact() { return &_supplyVoltageFact; }   //电源电压
    Fact *fuelLevelFact() { return &_fuelLevelFact; }           //燃油压力
    Fact *rotatingSpeedFact() { return &_rotatingSpeedFact; }   //发动机转速
    Fact *waterTemperatureFact() { return &_waterTemperatureFact; }//水温
    Fact *oilTemperatureFact() { return &_oilTemperatureFact; } //油温
    Fact *mainPumpPressureFact() { return &_mainPumpPressureFact; } //主泵压力
    Fact *frontPumpPressureFact() { return &_frontPumpPressureFact; } //前泵压力
    Fact *backPumpPressureFact() { return &_backPumpPressureFact; } //后泵压力
    Fact *oxygenConcentrationFact() { return &_oxygenConcentrationFact; }
    Fact *combustibleGasConcentrationFact() { return &_combustibleGasConcentrationFact; }
    Fact *AmbientTemperaturenFact() { return &_AmbientTemperaturenFact; }
    Fact *XDegreeFact() { return &_XDegreeFact; }
    Fact *YDegreeFact() { return &_YDegreeFact; }
    Fact *workHoursFact() { return &_workHoursFact; }

public:
    QStringList warningList;
    int dianyaWarning = 0;
    int shuiwenWarning = 0;
    int zhuansuWarning = 0;
    int ranyouWarning = 0;
    int youwenWarning = 0;
    int qianbengWarning = 0;
    int houbengWarning = 0;
    int xWarning = 0;
    int yWarning = 0;

private slots:
    void _updateAllValues() override;

private:
    Fact _carSpeedFact;
    Fact _oilPressureFact;
    Fact _airPressureFact;

    Fact _teleRSSIFact;
    Fact _supplyVoltageFact;
    Fact _fuelLevelFact;
    Fact _rotatingSpeedFact;
    Fact _waterTemperatureFact;
    Fact _oilTemperatureFact;
    Fact _mainPumpPressureFact;
    Fact _frontPumpPressureFact;
    Fact _backPumpPressureFact;
    Fact _oxygenConcentrationFact;
    Fact _combustibleGasConcentrationFact;
    Fact _AmbientTemperaturenFact;
    Fact _XDegreeFact;
    Fact _YDegreeFact;
    Fact _workHoursFact;

    static int testValue;

    static const char *_carSpeedFactName;
    static const char *_oilPressureFactName;
    static const char *_airPressureFactName;
    static const char *_teleRSSIFactName;
    static const char *_supplyVoltageFactName;
    static const char *_fuelLevelFactName;
    static const char *_rotatingSpeedFactName;
    static const char *_waterTemperatureFactName;
    static const char *_oilTemperatureFactName;
    static const char *_mainPumpPressureFactName;
    static const char *_frontPumpPressureFactName;
    static const char *_backPumpPressureFactName;
    static const char *_oxygenConcentrationFactName;
    static const char *_combustibleGasConcentrationFactName;
    static const char *_AmbientTemperaturenFactName;
    static const char *_XDegreeFactName;
    static const char *_YDegreeFactName;
    static const char *_workHoursFactName;

    static const int _vehicleUIUpdateRateMSecs = 200;

    CanLink *cl = nullptr;
    QStringList _warningEnum;
};

#endif // VEHICLE_H
