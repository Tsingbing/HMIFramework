#ifndef VEHICLE_H
#define VEHICLE_H

#include "FactGroup.h"
#include "Toolbox.h"
#include <QCanBusFrame>
#include <QObject>
#include <QMap>

#define DECLARE_FACT(NAME)                                \
public:                                                   \
    Q_PROPERTY(Fact* NAME##Fact READ NAME##Fact CONSTANT) \
    Fact* NAME##Fact();                                   \
                                                          \
private:                                                  \
    Fact               _##NAME##Fact;                     \
    static const char* _##NAME##Fact##Name;

class CanLink;

class EngineFactGroup : public FactGroup
{
    Q_OBJECT

public:
    EngineFactGroup(QObject* parent = nullptr);

    Q_PROPERTY(Fact* rotatingSpeedFact READ rotatingSpeedFact CONSTANT)
    Q_PROPERTY(Fact* xDegreeFact READ xDegreeFact CONSTANT)
    Q_PROPERTY(Fact* yDegreeFact READ yDegreeFact CONSTANT)

    Fact* rotatingSpeedFact() { return &_rotatingSpeedFact; }
    Fact* xDegreeFact() { return &_xDegreeFact; }
    Fact* yDegreeFact() { return &_yDegreeFact; }

    static const char* _rotatingSpeedFactName;
    static const char* _xDegreeFactName;
    static const char* _yDegreeFactName;
private slots:
    void _updateAllValues() override;
private:
    Fact _rotatingSpeedFact;
    Fact _xDegreeFact;
    Fact _yDegreeFact;

DECLARE_FACT(pochaiIsLock)
DECLARE_FACT(wajueIsLock)

};

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
    Q_PROPERTY(Fact* allSwitchsFact READ allSwitchsFact CONSTANT)
    Q_PROPERTY(QStringList warningsStrings READ warningsStrings NOTIFY warningsStringsChanged)
    //Q_PROPERTY(Fact* alarmsFact READ alarmsFact CONSTANT)

    Q_PROPERTY(FactGroup* engineFactGroup READ engineFactGroup CONSTANT)

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
    Fact* allSwitchsFact() { return &_allSwitchsFact; }
    //Fact* alarmsFact() { return &_alarmsFact; }
    FactGroup* engineFactGroup() { return &_engineFactGroup; }

    Q_INVOKABLE void sendFrontLightSwitch(bool b);
    Q_INVOKABLE void sendBackLightSwitch(bool b);
    Q_INVOKABLE void sendAlarmSwitch(bool b);
    Q_INVOKABLE void sendPoChaiLockSwitch(int b);
    Q_INVOKABLE void sendWajueLockSwitch(int b);
    Q_INVOKABLE void sendPoChaiQuickSwitch(int b);
    Q_INVOKABLE void sendReadControl(bool b);
    Q_INVOKABLE void sendWriteControl(bool b);
    Q_INVOKABLE void sendJiesuo(bool b);

    Q_INVOKABLE void updateAllParams();
    // Property accesors
    int id() { return _id; }

    QStringList warningsStrings() const
    {
        return _warningsStrings;
    }

signals:
    void warningsStringsChanged(QStringList warningsStrings);

private slots:
    void _updateAllValues() override;
    void _canframesRecived(QCanBusFrame data);

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
    Fact       _allSwitchsFact;
    //Fact       _alarmsFact;

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
    static const char* _allSwitchsFactName;
    //static const char* _alarmsFactName;
    static const int   _vehicleUIUpdateRateMSecs = 3000; //0: 立即刷新
    static const int   _id                       = 100;

    CanLink* cl = nullptr;
    DECLARE_FACT(batteryPower)
    DECLARE_FACT(upperLimitLeftTrackHighSpeed)
    DECLARE_FACT(upperLimitLeftTrackLowSpeed)
    DECLARE_FACT(upperLimitLeftTrackFrettingSpeed)
    DECLARE_FACT(lowerLimitLeftTrackSpeed)
    DECLARE_FACT(upperLimitRightTrackHighSpeed)
    DECLARE_FACT(upperLimitRightTrackLowSpeed)
    DECLARE_FACT(upperLimitRightTrackFrettingSpeed)
    DECLARE_FACT(lowerLimitRightTrackSpeed)
    DECLARE_FACT(alarms)
    DECLARE_FACT(upperLimitLeftTrackBackHighSpeed)
    DECLARE_FACT(upperLimitLeftTrackBackLowSpeed)
    DECLARE_FACT(upperLimitRightTrackBackHighSpeed)
    DECLARE_FACT(upperLimitRightTrackBackLowSpeed)


    static const char* _engineFactGroupName;
    EngineFactGroup _engineFactGroup;

    QStringList _warningsStrings;
    QMap<QString, QString> _warningsStringsQMap;
};

#endif // VEHICLE_H
