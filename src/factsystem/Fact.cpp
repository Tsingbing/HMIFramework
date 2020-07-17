#include "Fact.h"

Fact::Fact(QObject *parent)
    : QObject(parent)
    , _metaData(nullptr)
{

}

Fact::Fact(QString name, FactMetaData::ValueType_t type, QObject *parent)
    : QObject(parent)
    , _name(name)
    , _rawValue(0)
    , _type(type)
    , _metaData(nullptr)
{
    FactMetaData* metaData = new FactMetaData(_type, this);
    setMetaData(metaData);
}

QString Fact::name() const
{
    return _name;
}

FactMetaData::ValueType_t Fact::type() const
{
    return _type;
}

QString Fact::shortDescription() const
{
    //    if (_metaData) {
    //        return _metaData->shortDescription();
    //    } else {
    //        qWarning() << kMissingMetadata << name();
            return QString();
    //    }
}

QString Fact::rawValueString() const
{
    return _variantToString(rawValue(), 2);
}

void Fact::setRawValue(const QVariant &value)
{
    _rawValue.setValue(value);
    //    if (_metaData) {
    //        QVariant    typedValue;
    //        QString     errorString;

    //        if (_metaData->convertAndValidateRaw(value, true /* convertOnly */, typedValue, errorString)) {
    //            if (typedValue != _rawValue) {
    //                _rawValue.setValue(typedValue);
    //                _sendValueChangedSignal(cookedValue());
    //                //-- Must be in this order
    //                emit _containerRawValueChanged(rawValue());
    //                emit rawValueChanged(_rawValue);
    //            }
    //        }
    //    } else {
    //        qWarning() << kMissingMetadata << name();
    //    }
}

void Fact::setMetaData(FactMetaData *metaData, bool setDefaultFromMetaData)
{
    //    _metaData = metaData;
    //    if (setDefaultFromMetaData) {
    //        setRawValue(rawDefaultValue());
    //    }
    //    emit valueChanged(cookedValue());
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
