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
    Fact *supplyVoltageFact() { return &_supplyVoltageFact; }
    Fact *fuelLevelFact() { return &_fuelLevelFact; }
    Fact *rotatingSpeedFact() { return &_rotatingSpeedFact; }
    Fact *waterTemperatureFact() { return &_waterTemperatureFact; }
    Fact *mainPumpPressureFact() { return &_mainPumpPressureFact; }
    Fact *oxygenConcentrationFact() { return &_oxygenConcentrationFact; }
    Fact *combustibleGasConcentrationFact() { return &_combustibleGasConcentrationFact; }
    Fact *AmbientTemperaturenFact() { return &_AmbientTemperaturenFact; }
    Fact *XDegreeFact() { return &_XDegreeFact; }
    Fact *YDegreeFact() { return &_YDegreeFact; }
    Fact *workHoursFact() { return &_workHoursFact; }

    void sendFrontLightSwitch(bool b);
    void sendBackLightSwitch(bool b);
    void sendAlarmSwitch(bool b);
    void sendPoChaiLockSwitch(bool b);
    void sendWajueLockSwitch(bool b);
    void sendPoChaiQuickSwitch(bool b);

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
    Fact _mainPumpPressureFact;
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
    static const char *_mainPumpPressureFactName;
    static const char *_oxygenConcentrationFactName;
    static const char *_combustibleGasConcentrationFactName;
    static const char *_AmbientTemperaturenFactName;
    static const char *_XDegreeFactName;
    static const char *_YDegreeFactName;
    static const char *_workHoursFactName;

    static const int _vehicleUIUpdateRateMSecs = 0;

    CanLink *cl = nullptr;
};

#endif // VEHICLE_H
