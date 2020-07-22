#include "Vehicle.h"
#include <QSettings>

const char* Vehicle::_speedFactName =            "speed";

Vehicle::Vehicle(QObject *parent)
    : FactGroup(_vehicleUIUpdateRateMSecs, ":/json/Vehicle/VehicleFact.json", parent)
{
    {
        //速度
        FactMetaData* metaData = new FactMetaData(FactMetaData::valueTypeDouble, "Speed", this);
        metaData->setShortDescription("Speed");
        metaData->setDecimalPlaces(3);
        metaData->setRawUnits("km/h");
        metaData->setRawDefaultValue(QVariant(10));
        metaData->setRawMax(60);
        metaData->setRawMin(0);

        _speedFact = new Fact(metaData, this);
        //_speedFact->setRawValue(50.6666);
    }

    {
        //转速
        FactMetaData* metaData = new FactMetaData(FactMetaData::valueTypeInt32, "RotatingSpeed", this);
        metaData->setShortDescription("Rotating Speed");
        metaData->setDecimalPlaces(3);
        metaData->setRawUnits("RPS");
        metaData->setRawDefaultValue(QVariant(110));
        metaData->setRawMax(2500);
        metaData->setRawMin(0);

        _rotatingSpeedFact = new Fact(metaData, this);
        //_rotatingSpeedFact->setRawValue(7089.6666);
    }

    QSettings settings;
    settings.setValue("test", true);
    settings.beginGroup("speed");
    settings.setValue("speed", _speedFact->rawValueString());
    settings.endGroup();

}
