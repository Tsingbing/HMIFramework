#ifndef VEHICLE_H
#define VEHICLE_H

#include <QObject>
#include "FactGroup.h"

class Vehicle : public FactGroup
{
    Q_OBJECT
public:
    Vehicle(QObject* parent = nullptr);

    Fact* carSpeedFact() {return &_carSpeedFact;}
    Fact* rotatingSpeedFact() { return &_rotatingSpeedFact;}
    Fact* oilPressureFact() { return &_oilPressureFact;}
    Fact* waterTemperatureFact() { return &_waterTemperatureFact;}
    Fact* airPressureFact() { return &_airPressureFact;}
private slots:
    void _updateValue();

private:
    void _setupTimer();
    QTimer _updateTime;

    Fact _carSpeedFact;
    Fact _rotatingSpeedFact;
    Fact _oilPressureFact;
    Fact _waterTemperatureFact;
    Fact _airPressureFact;

    static int testValue;

    static const char* _carSpeedFactName;
    static const char* _rotatingSpeedFactName;
    static const char* _oilPressureFactName;
    static const char* _waterTemperatureFactName;
    static const char* _airPressureFactName;

    static const int _vehicleUIUpdateRateMSecs = 100;
};

#endif // VEHICLE_H
