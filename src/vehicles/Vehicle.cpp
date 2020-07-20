#include "Vehicle.h"
#include <QSettings>

const char* Vehicle::_speedFactName =            "speed";

Vehicle::Vehicle(QObject *parent)
    : FactGroup(_vehicleUIUpdateRateMSecs, ":/json/Vehicle/VehicleFact.json", parent)
    , _speedFact(_speedFactName, FactMetaData::valueTypeDouble)
{
    _speedFact.setRawValue(5.1011111);

    QSettings settings;
    settings.setValue("test", true);
    settings.beginGroup("speed");
    settings.setValue("speed", _speedFact.rawValue());
    settings.endGroup();

    {
        //转速
        FactMetaData* metaData = new FactMetaData(FactMetaData::valueTypeInt32, "RotatingSpeed", this);
        metaData->setShortDescription("Rotating Speed");
        metaData->setDecimalPlaces(3);
        //metaData->
        _rotatingSpeedFact = new Fact(metaData, this);
        _rotatingSpeedFact->setRawValue(789);
    }
}
