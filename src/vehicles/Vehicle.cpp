#include "Vehicle.h"

const char* Vehicle::_speedFactName =            "speed";

Vehicle::Vehicle(QObject *parent)
    : FactGroup(_vehicleUIUpdateRateMSecs, ":/json/Vehicle/VehicleFact.json")
    , _speedFact(_speedFactName, FactMetaData::valueTypeDouble)
{
    _speedFact.setRawValue(5.1011111);
}
