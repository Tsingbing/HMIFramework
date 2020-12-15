#include "Fact.h"
#include <QDebug>
static const char* kMissingMetadata = "Meta data pointer missing";

Fact::Fact(QObject *parent)
    : QObject(parent)
    , _rawValue (0)
    , _type     (FactMetaData::valueTypeInt32)
    , _metaData (0)
{
    FactMetaData* metaData = new FactMetaData(_type, this);
    setMetaData(metaData);
}

Fact::Fact(QString name, FactMetaData::ValueType_t type, QObject *parent)
    : QObject(parent)
    , _name(name)
    , _rawValue(0)
    , _type(type)
    , _metaData(0)
{
    FactMetaData* metaData = new FactMetaData(_type, this);
    setMetaData(metaData,true /* setDefaultFromMetaData */);
}

Fact::Fact(FactMetaData *metaData, QObject *parent)
    : QObject   (parent)
    , _name     (metaData->name())
    , _rawValue (0)
    , _type     (metaData->type())
    , _metaData (metaData)
{
    setMetaData(metaData,true /* setDefaultFromMetaData */);
}

QString Fact::name() const
{
    return _name;
}

FactMetaData::ValueType_t Fact::type() const
{
    //此处逻辑有点问题，返回metaData的类型。
    if (_metaData) {
        return _metaData->type();
    } else {
        qWarning() << kMissingMetadata << type();
        //return 0; // 需要确定返回值。。。
    }
    //return _type;
}

QString Fact::shortDescription() const
{
    if (_metaData) {
        return _metaData->shortDescription();
    } else {
        qWarning() << kMissingMetadata << name();
        return QString();
    }
}

int Fact::decimalPlaces() const
{
    if (_metaData) {
        return _metaData->decimalPlaces();
    } else {
        qWarning() << kMissingMetadata << name();
        return FactMetaData::kDefaultDecimalPlaces;
    }
}

QVariant Fact::rawDefaultValue() const
{
    if (_metaData) {
        //if (!_metaData->defaultValueAvailable()) {
        //    qDebug() << "Access to unavailable default value";
        // }
        return _metaData->rawDefaultValue();
    } else {
        qWarning() << kMissingMetadata << name();
        return QVariant(0);
    }
}

QVariant Fact::rawMax() const
{
    if (_metaData) {
        return _metaData->rawMax();
    } else {
        qWarning() << kMissingMetadata << name();
        return QVariant(0);
    }
}

QVariant Fact::rawMin() const
{
    if (_metaData) {
        return _metaData->rawMin();
    } else {
        qWarning() << kMissingMetadata << name();
        return QVariant(0);
    }
}

QString Fact::rawUnits() const
{
    if (_metaData) {
        return _metaData->rawUnits();
    } else {
        qWarning() << kMissingMetadata << name();
        return QString();
    }
}

QString Fact::units() const
{
    if (_metaData) {
        return _metaData->cookedUnits();
    } else {
        qWarning() << kMissingMetadata << name();
        return QString();
    }
}

QVariant Fact::value() const
{
    if (_metaData) {
        return _metaData->defaultTranslator(_rawValue); //默认转换器
    } else {
        qWarning() << kMissingMetadata << name();
        return _rawValue;
    }
}


QString Fact::rawValueString() const
{
    return _variantToString(rawValue(), decimalPlaces());
}

QString Fact::valueString() const
{
    return _variantToString(value(), decimalPlaces());
}

void Fact::setRawValue(const QVariant &value)
{
    if (_metaData) {
        QVariant    typedValue;
        QString     errorString;

        if (_metaData->convertAndValidateRaw(value, true /* convertOnly */, typedValue, errorString)) {
            if (typedValue != _rawValue) {
                _rawValue.setValue(typedValue);
                //_sendValueChangedSignal(cookedValue());
                //-- Must be in this order
                //emit _containerRawValueChanged(rawValue());
                //emit rawValueChanged(_rawValue);
                emit valueChanged();
            }
        }
    } else {
        qWarning() << kMissingMetadata << name();
    }
}

void Fact::setMetaData(FactMetaData *metaData, bool setDefaultFromMetaData)
{
    _metaData = metaData;
    if (setDefaultFromMetaData) {
        setRawValue(rawDefaultValue());
    }
    //emit valueChanged(cookedValue());
}

QString Fact::_variantToString(const QVariant &variant, int decimalPlaces) const
{
    QString valueString;

    switch (type()) {
    case FactMetaData::valueTypeFloat:
    {
        float fValue = variant.toFloat();
        if (qIsNaN(fValue)) {
            valueString = QStringLiteral("--.--");
        } else {
            valueString = QString("%1").arg(fValue, 0, 'f', decimalPlaces);
        }
    }
        break;
    case FactMetaData::valueTypeDouble:
    {
        double dValue = variant.toDouble();
        if (qIsNaN(dValue)) {
            valueString = QStringLiteral("--.--");
        } else {
            valueString = QString("%1").arg(dValue, 0, 'f', decimalPlaces);
        }
    }
        break;
    case FactMetaData::valueTypeBool:
        valueString = variant.toBool() ? tr("true") : tr("false");
        break;
        //    case FactMetaData::valueTypeElapsedTimeInSeconds:
        //    {
        //        double dValue = variant.toDouble();
        //        if (qIsNaN(dValue)) {
        //            valueString = QStringLiteral("--:--:--");
        //        } else {
        //            QTime time(0, 0, 0, 0);
        //            time = time.addSecs(dValue);
        //            valueString = time.toString(QStringLiteral("hh:mm:ss"));
        //        }
        //    }
        //        break;
    default:
        valueString = variant.toString();
        break;
    }

    return valueString;
}
