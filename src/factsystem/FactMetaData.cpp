#include "FactMetaData.h"

const char* FactMetaData::_decimalPlacesJsonKey =       "decimalPlaces";
const char* FactMetaData::_nameJsonKey =                "name";
const char* FactMetaData::_typeJsonKey =                "type";
const char* FactMetaData::_shortDescriptionJsonKey =    "shortDescription";
const char* FactMetaData::_unitsJsonKey =               "units";
const char* FactMetaData::_defaultValueJsonKey =        "defaultValue";
const char* FactMetaData::_minJsonKey =                 "min";
const char* FactMetaData::_maxJsonKey =                 "max";

FactMetaData::FactMetaData(FactMetaData::ValueType_t type, const QString name, QObject *parent)
    : QObject(parent)
    , _type                 (type)
    , _name                 (name)
    , _rawMax               (_maxForType())
    , _rawMin               (_minForType())
    , _decimalPlaces        (kUnknownDecimalPlaces)
    , _rawDefaultValue      (0)
{

}

int FactMetaData::decimalPlaces() const
{
    return _decimalPlaces;
}

QVariant FactMetaData::rawDefaultValue() const
{
    return _rawDefaultValue;
}

void FactMetaData::setRawMax(const QVariant &rawMax)
{
    if (rawMax > _maxForType()) {
        //qWarning() << "Attempt to set max above allowable value";
        _rawMax = _maxForType();
    } else {
        _rawMax = rawMax;
        //_maxIsDefaultForType = false;
    }
}

void FactMetaData::setRawMin(const QVariant &rawMin)
{
    if (rawMin >= _minForType()) {
        _rawMin = rawMin;
        //_minIsDefaultForType = false;
    } else {
        //        qWarning() << "Attempt to set min below allowable value for fact: " << name()
        //                   << ", value attempted: " << rawMin
        //                   << ", type: " << type() << ", min for type: " << _minForType();
        _rawMin = _minForType();
    }
}


QVariant FactMetaData::_minForType() const
{
    switch (_type) {
    case valueTypeUint8:
        return QVariant(std::numeric_limits<unsigned char>::min());
    case valueTypeInt8:
        return QVariant(std::numeric_limits<signed char>::min());
    case valueTypeUint16:
        return QVariant(std::numeric_limits<unsigned short int>::min());
    case valueTypeInt16:
        return QVariant(std::numeric_limits<short int>::min());
    case valueTypeUint32:
        return QVariant(std::numeric_limits<uint32_t>::min());
    case valueTypeInt32:
        return QVariant(std::numeric_limits<int32_t>::min());
    case valueTypeUint64:
        return QVariant((qulonglong)std::numeric_limits<uint64_t>::min());
    case valueTypeInt64:
        return QVariant((qlonglong)std::numeric_limits<int64_t>::min());
    case valueTypeFloat:
        return QVariant(-std::numeric_limits<float>::max());
    case valueTypeDouble:
        return QVariant(-std::numeric_limits<double>::max());
    case valueTypeString:
        return QVariant();
    case valueTypeBool:
        return QVariant(0);
    }

    // Make windows compiler happy, even switch is full cased
    return QVariant();
}

QVariant FactMetaData::_maxForType() const
{
    switch (_type) {
    case valueTypeUint8:
        return QVariant(std::numeric_limits<unsigned char>::max());
    case valueTypeInt8:
        return QVariant(std::numeric_limits<signed char>::max());
    case valueTypeUint16:
        return QVariant(std::numeric_limits<unsigned short int>::max());
    case valueTypeInt16:
        return QVariant(std::numeric_limits<short int>::max());
    case valueTypeUint32:
        return QVariant(std::numeric_limits<uint32_t>::max());
    case valueTypeInt32:
        return QVariant(std::numeric_limits<int32_t>::max());
    case valueTypeUint64:
        return QVariant((qulonglong)std::numeric_limits<uint64_t>::max());
    case valueTypeInt64:
        return QVariant((qlonglong)std::numeric_limits<int64_t>::max());
    case valueTypeFloat:
        return QVariant(std::numeric_limits<float>::max());
    case valueTypeDouble:
        return QVariant(std::numeric_limits<double>::max());
    case valueTypeString:
        return QVariant();
    case valueTypeBool:
        return QVariant(1);
    }

    // Make windows compiler happy, even switch is full cased
    return QVariant();
}

