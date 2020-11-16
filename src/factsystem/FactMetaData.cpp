#include "FactMetaData.h"
#include <QDebug>
#include "JsonHelper.h"

#include <QDebug>
#include <QtMath>
#include <QJsonParseError>
#include <QJsonArray>
#include <QFile>

const char* FactMetaData::_decimalPlacesJsonKey =       "decimalPlaces";
const char* FactMetaData::_nameJsonKey =                "name";
const char* FactMetaData::_typeJsonKey =                "type";
const char* FactMetaData::_shortDescriptionJsonKey =    "shortDescription";
const char* FactMetaData::_unitsJsonKey =               "units";
const char* FactMetaData::_defaultValueJsonKey =        "defaultValue";
const char* FactMetaData::_minJsonKey =                 "min";
const char* FactMetaData::_maxJsonKey =                 "max";

FactMetaData::FactMetaData(FactMetaData::ValueType_t type, QObject *parent)
    : QObject(parent)
    , _type                 (type)
    , _rawMax               (_maxForType())
    , _rawMin               (_minForType())
    , _decimalPlaces        (kUnknownDecimalPlaces)
    , _rawDefaultValue      (0)
{

}

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

QMap<QString, FactMetaData *> FactMetaData::createMapFromJsonFile(const QString &jsonFilename, QObject *metaDataParent)
{
    QMap<QString, FactMetaData*> metaDataMap;

    QFile jsonFile(jsonFilename);
    if (!jsonFile.open(QIODevice::ReadOnly | QIODevice::Text)) {
        qWarning() << "Unable to open file" << jsonFilename << jsonFile.errorString();
        return metaDataMap;
    }

    QByteArray bytes = jsonFile.readAll();
    jsonFile.close();
    QJsonParseError jsonParseError;
    QJsonDocument doc = QJsonDocument::fromJson(bytes, &jsonParseError);
    if (jsonParseError.error != QJsonParseError::NoError) {
        qWarning() <<  "Unable to parse json document filename:error:offset" << jsonFilename << jsonParseError.errorString() << jsonParseError.offset;
        return metaDataMap;
    }

    QJsonArray factArray;
    QMap<QString /* define name */, QString /* define value */> defineMap;

    if (doc.isArray()) {
        factArray = doc.array();
    } else {
        qWarning() << "Json document is neither array nor object";
        return metaDataMap;
    }

    return createMapFromJsonArray(factArray, defineMap, metaDataParent);
}

QMap<QString, FactMetaData *> FactMetaData::createMapFromJsonArray(const QJsonArray jsonArray, QMap<QString, QString> &defineMap, QObject *metaDataParent)
{
    QMap<QString, FactMetaData*> metaDataMap;
    for (int i=0; i<jsonArray.count(); i++) {
        QJsonValue jsonValue = jsonArray.at(i);
        if (!jsonValue.isObject()) {
            qWarning() << QStringLiteral("JsonValue at index %1 not an object").arg(i);
            continue;
        }
        QJsonObject jsonObject = jsonValue.toObject();
        FactMetaData* metaData = createFromJsonObject(jsonObject, defineMap, metaDataParent);
        if (metaDataMap.contains(metaData->name())) {
            qWarning() << QStringLiteral("Duplicate fact name:") << metaData->name();
            delete metaData;
        } else {
            metaDataMap[metaData->name()] = metaData;
        }
    }
    return metaDataMap;
}

FactMetaData *FactMetaData::createFromJsonObject(const QJsonObject &json, QMap<QString, QString> &defineMap, QObject *metaDataParent)
{
    QString         errorString;

    // Make sure we have the required keys
    QStringList requiredKeys;
    requiredKeys << _nameJsonKey << _typeJsonKey;
    if (!JsonHelper::validateRequiredKeys(json, requiredKeys, errorString)) {
        qWarning() << errorString;
        return new FactMetaData(valueTypeUint32, metaDataParent);
    }

    QList<JsonHelper::KeyValidateInfo> keyInfoList = {
        { _nameJsonKey,                 QJsonValue::String, true },
        { _typeJsonKey,                 QJsonValue::String, true },
        { _shortDescriptionJsonKey,     QJsonValue::String, false },
        //{ _longDescriptionJsonKey,      QJsonValue::String, false },
        { _unitsJsonKey,                QJsonValue::String, false },
        { _decimalPlacesJsonKey,        QJsonValue::Double, false },
        { _minJsonKey,                  QJsonValue::Double, false },
        { _maxJsonKey,                  QJsonValue::Double, false },
        //{ _hasControlJsonKey,           QJsonValue::Bool,   false },
        //{ _qgcRebootRequiredJsonKey,    QJsonValue::Bool,   false },
    };
    if (!JsonHelper::validateKeys(json, keyInfoList, errorString)) {
        qWarning() << errorString;
        return new FactMetaData(valueTypeUint32, metaDataParent);
    }

    bool unknownType;
    FactMetaData::ValueType_t type = FactMetaData::stringToType(json[_typeJsonKey].toString(), unknownType);
    if (unknownType) {
        qWarning() << "Unknown type" << json[_typeJsonKey].toString();
        return new FactMetaData(valueTypeUint32, metaDataParent);
    }

    FactMetaData*   metaData = new FactMetaData(type, metaDataParent);

    metaData->_name = json[_nameJsonKey].toString();

    QStringList enumValues, enumStrings;
    if (JsonHelper::parseEnum(json, defineMap, enumStrings, enumValues, errorString, metaData->name())) {
        for (int i=0; i<enumValues.count(); i++) {
            QVariant    enumVariant;
            QString     errorString;

            if (metaData->convertAndValidateRaw(enumValues[i], false /* validate */, enumVariant, errorString)) {
                //metaData->addEnumInfo(enumStrings[i], enumVariant);
            } else {
                qWarning() << "Invalid enum value, name:" << metaData->name()
                           << " type:" << metaData->type()
                           << " value:" << enumValues[i]
                              << " error:" << errorString;
            }
        }
    } else {
        qWarning() << errorString;
    }

    metaData->setDecimalPlaces(json[_decimalPlacesJsonKey].toInt(0));
    metaData->setShortDescription(json[_shortDescriptionJsonKey].toString());

    if (json.contains(_unitsJsonKey)) {
        metaData->setRawUnits(json[_unitsJsonKey].toString());
    }

    QString defaultValueJsonKey;

    if (defaultValueJsonKey.isEmpty() && json.contains(_defaultValueJsonKey)) {
        defaultValueJsonKey = _defaultValueJsonKey;
    }
    if (!defaultValueJsonKey.isEmpty()) {
        QVariant typedValue;
        QString errorString;
        QVariant initialValue = json[defaultValueJsonKey].toVariant();
        if (metaData->convertAndValidateRaw(initialValue, true /* convertOnly */, typedValue, errorString)) {
            metaData->setRawDefaultValue(typedValue);
        } else {
            qWarning() << "Invalid default value, name:" << metaData->name()
                       << " type:" << metaData->type()
                       << " value:" << initialValue
                       << " error:" << errorString;
        }
    }

    if (json.contains(_minJsonKey)) {
        QVariant typedValue;
        QString errorString;
        QVariant initialValue = json[_minJsonKey].toVariant();
        if (metaData->convertAndValidateRaw(initialValue, true /* convertOnly */, typedValue, errorString)) {
            metaData->setRawMin(typedValue);
        } else {
            qWarning() << "Invalid min value, name:" << metaData->name()
                       << " type:" << metaData->type()
                       << " value:" << initialValue
                       << " error:" << errorString;
        }
    }

    if (json.contains(_maxJsonKey)) {
        QVariant typedValue;
        QString errorString;
        QVariant initialValue = json[_maxJsonKey].toVariant();
        if (metaData->convertAndValidateRaw(initialValue, true /* convertOnly */, typedValue, errorString)) {
            metaData->setRawMax(typedValue);
        } else {
            qWarning() << "Invalid max value, name:" << metaData->name()
                       << " type:" << metaData->type()
                       << " value:" << initialValue
                       << " error:" << errorString;
        }
    }

    return metaData;
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

void FactMetaData::setRawDefaultValue(const QVariant &rawDefaultValue)
{
    if(_type == valueTypeString || (_rawMin <= rawDefaultValue && rawDefaultValue <= _rawMax)){
        _rawDefaultValue = rawDefaultValue;
    } else {
        qWarning() << "Attempt to set default value which is outside min/max range.";
    }
}

bool FactMetaData::convertAndValidateRaw(const QVariant &rawValue, bool convertOnly, QVariant &typedValue, QString &errorString)
{
    bool convertOk = false;

    errorString.clear();

    switch (type()) {
    case FactMetaData::valueTypeInt8:
    case FactMetaData::valueTypeInt16:
    case FactMetaData::valueTypeInt32:
        typedValue = QVariant(rawValue.toInt(&convertOk));
        if (!convertOnly && convertOk) {
            if (typedValue < rawMin() || typedValue > rawMax()) {
                errorString = tr("Value must be within %1 and %2").arg(rawMin().toInt()).arg(rawMax().toInt());
            }
        }
        break;
    case FactMetaData::valueTypeInt64:
        typedValue = QVariant(rawValue.toLongLong(&convertOk));
        if (!convertOnly && convertOk) {
            if (typedValue < rawMin() || typedValue > rawMax()) {
                errorString = tr("Value must be within %1 and %2").arg(rawMin().toInt()).arg(rawMax().toInt());
            }
        }
        break;
    case FactMetaData::valueTypeUint8:
    case FactMetaData::valueTypeUint16:
    case FactMetaData::valueTypeUint32:
        typedValue = QVariant(rawValue.toUInt(&convertOk));
        if (!convertOnly && convertOk) {
            if (typedValue < rawMin() || typedValue > rawMax()) {
                errorString = tr("Value must be within %1 and %2").arg(rawMin().toUInt()).arg(rawMax().toUInt());
            }
        }
        break;
    case FactMetaData::valueTypeUint64:
        typedValue = QVariant(rawValue.toULongLong(&convertOk));
        if (!convertOnly && convertOk) {
            if (typedValue < rawMin() || typedValue > rawMax()) {
                errorString = tr("Value must be within %1 and %2").arg(rawMin().toUInt()).arg(rawMax().toUInt());
            }
        }
        break;
    case FactMetaData::valueTypeFloat:
        typedValue = QVariant(rawValue.toFloat(&convertOk));
        if (!convertOnly && convertOk) {
            if (typedValue < rawMin() || typedValue > rawMax()) {
                errorString = tr("Value must be within %1 and %2").arg(rawMin().toDouble()).arg(rawMax().toDouble());
            }
        }
        break;
    case FactMetaData::valueTypeDouble:
        typedValue = QVariant(rawValue.toDouble(&convertOk));
        if (!convertOnly && convertOk) {
            if (typedValue < rawMin() || typedValue > rawMax()) {
                errorString = tr("Value must be within %1 and %2").arg(rawMin().toDouble()).arg(rawMax().toDouble());
            }
        }
        break;
    case FactMetaData::valueTypeString:
        convertOk = true;
        typedValue = QVariant(rawValue.toString());
        break;
    case FactMetaData::valueTypeBool:
        convertOk = true;
        typedValue = QVariant(rawValue.toBool());
        break;
    }

    if (!convertOk) {
        errorString += tr("Invalid number");
    }

    return convertOk && errorString.isEmpty();
}

FactMetaData::ValueType_t FactMetaData::stringToType(const QString &typeString, bool &unknownType)
{
    QStringList         knownTypeStrings;
    QList<ValueType_t>  knownTypes;

    unknownType = false;

    knownTypeStrings << QStringLiteral("Uint8")
                     << QStringLiteral("Int8")
                     << QStringLiteral("Uint16")
                     << QStringLiteral("Int16")
                     << QStringLiteral("Uint32")
                     << QStringLiteral("Int32")
                     << QStringLiteral("Uint64")
                     << QStringLiteral("Int64")
                     << QStringLiteral("Float")
                     << QStringLiteral("Double")
                     << QStringLiteral("String")
                     << QStringLiteral("Bool");

    knownTypes << valueTypeUint8
               << valueTypeInt8
               << valueTypeUint16
               << valueTypeInt16
               << valueTypeUint32
               << valueTypeInt32
               << valueTypeUint64
               << valueTypeInt64
               << valueTypeFloat
               << valueTypeDouble
               << valueTypeString
               << valueTypeBool;

    for (int i=0; i<knownTypeStrings.count(); i++) {
        if (knownTypeStrings[i].compare(typeString, Qt::CaseInsensitive) == 0) {
            return knownTypes[i];
        }
    }

    unknownType = true;

    return valueTypeDouble;
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

    return QVariant();
}

