#ifndef VEHICLE_H
#define VEHICLE_H

#include "FactGroup.h"
#include "Toolbox.h"
#include <QCanBusFrame>
#include <QObject>

class CanLink;

class Vehicle : public FactGroup
{
    Q_OBJECT
public:
    Vehicle(QObject* parent = nullptr);

    Q_PROPERTY(int id READ id CONSTANT)
    Q_PROPERTY(Fact* supplyVoltageFact READ supplyVoltageFact CONSTANT)
    Q_PROPERTY(Fact* fuelLevelFact READ fuelLevelFact CONSTANT)
    Q_PROPERTY(Fact* rotatingSpeedFact READ rotatingSpeedFact CONSTANT)
    Q_PROPERTY(Fact* waterTemperatureFact READ waterTemperatureFact CONSTANT)
    Q_PROPERTY(Fact* oxygenConcentrationFact READ oxygenConcentrationFact CONSTANT)
    Q_PROPERTY(Fact* mainPumpPressureFact READ mainPumpPressureFact CONSTANT)
    Q_PROPERTY(Fact* combustibleGasConcentrationFact READ combustibleGasConcentrationFact CONSTANT)
    Q_PROPERTY(Fact* ambientTemperaturenFact READ ambientTemperaturenFact CONSTANT)
    Q_PROPERTY(Fact* xDegreeFact READ xDegreeFact CONSTANT)
    Q_PROPERTY(Fact* yDegreeFact READ yDegreeFact CONSTANT)
    Q_PROPERTY(Fact* workHoursFact READ workHoursFact CONSTANT)
    Q_PROPERTY(Fact* oilTemperatureFact READ oilTemperatureFact CONSTANT)

    Q_INVOKABLE void forceArm();

    Fact* teleRSSIFact() { return &_teleRSSIFact; }
    Fact* supplyVoltageFact() { return &_supplyVoltageFact; }
    Fact* fuelLevelFact() { return &_fuelLevelFact; }
    Fact* rotatingSpeedFact() { return &_rotatingSpeedFact; }
    Fact* waterTemperatureFact() { return &_waterTemperatureFact; }
    Fact* mainPumpPressureFact() { return &_mainPumpPressureFact; }
    Fact* oxygenConcentrationFact() { return &_oxygenConcentrationFact; }
    Fact* combustibleGasConcentrationFact() { return &_combustibleGasConcentrationFact; }
    Fact* ambientTemperaturenFact() { return &_ambientTemperaturenFact; }
    Fact* xDegreeFact() { return &_xDegreeFact; }
    Fact* yDegreeFact() { return &_yDegreeFact; }
    Fact* workHoursFact() { return &_workHoursFact; }
    Fact* oilTemperatureFact() { return &_oilTemperatureFact; }

    Fact* frontLightFact() { return &_frontLightFact; }
    Fact* backLightFact() { return &_backLightFact; }
    Fact* alarmLightFact() { return &_alarmLightFact; }
    Fact* poChaiLockFact() { return &_poChaiLockFact; }
    Fact* wajueLockFact() { return &_wajueLockFact; }
    Fact* poChaiQuickFact() { return &_poChaiQuickFact; }

    Q_INVOKABLE void sendFrontLightSwitch(bool b);
    Q_INVOKABLE void sendBackLightSwitch(bool b);
    Q_INVOKABLE void sendAlarmSwitch(bool b);
    Q_INVOKABLE void sendPoChaiLockSwitch(bool b);
    Q_INVOKABLE void sendWajueLockSwitch(bool b);
    Q_INVOKABLE void sendPoChaiQuickSwitch(bool b);
    Q_INVOKABLE void sendReadControl(bool b);
    Q_INVOKABLE void sendWriteControl(bool b);

    // Property accesors
    int id() { return _id; }

private slots:
    void _updateAllValues() override;

private:
    void _commonInit();

private:
    Fact _teleRSSIFact;
    Fact _supplyVoltageFact;
    Fact _fuelLevelFact;
    Fact _rotatingSpeedFact;
    Fact _waterTemperatureFact;
    Fact _mainPumpPressureFact;
    Fact _oxygenConcentrationFact;
    Fact _combustibleGasConcentrationFact;
    Fact _ambientTemperaturenFact;
    Fact _xDegreeFact;
    Fact _yDegreeFact;
    Fact _workHoursFact;
    Fact _oilTemperatureFact;

    QByteArray _switch = QByteArray::fromHex("0000000000000000");
    Fact       _frontLightFact;
    Fact       _backLightFact;
    Fact       _alarmLightFact;
    Fact       _poChaiLockFact;
    Fact       _wajueLockFact;
    Fact       _poChaiQuickFact;

    static int testValue;

    static const char* _teleRSSIFactName;
    static const char* _supplyVoltageFactName;
    static const char* _fuelLevelFactName;
    static const char* _rotatingSpeedFactName;
    static const char* _waterTemperatureFactName;
    static const char* _mainPumpPressureFactName;
    static const char* _oxygenConcentrationFactName;
    static const char* _combustibleGasConcentrationFactName;
    static const char* _ambientTemperaturenFactName;
    static const char* _xDegreeFactName;
    static const char* _yDegreeFactName;
    static const char* _workHoursFactName;
    static const char* _oilTemperatureFactName;

    static const char* _frontLightFactName;
    static const char* _backLightFactName;
    static const char* _alarmLightFactName;
    static const char* _poChaiLockFactName;
    static const char* _wajueLockFactName;
    static const char* _poChaiQuickFactName;

    static const int _vehicleUIUpdateRateMSecs = 100; //0: 立即刷新
    static const int _id                       = 100;

    CanLink* cl = nullptr;
};

#endif // VEHICLE_H
