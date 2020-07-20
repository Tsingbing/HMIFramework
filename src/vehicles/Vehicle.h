#ifndef VEHICLE_H
#define VEHICLE_H

#include <QObject>
#include "FactGroup.h"

class Vehicle : public FactGroup
{
    Q_OBJECT
public:
    Vehicle(QObject* parent = nullptr);

    Fact* speedFact() {return & _speedFact;}
    Fact* rotatingSpeedFact() { return _rotatingSpeedFact;}

private:
    Fact _speedFact;
    Fact* _rotatingSpeedFact;

    static const char* _speedFactName;

    static const int _vehicleUIUpdateRateMSecs = 100;
};

#endif // VEHICLE_H
