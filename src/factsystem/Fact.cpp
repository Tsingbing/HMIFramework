#include "Fact.h"
#include <QDebug>
static const char* kMissingMetadata = "Meta data pointer missing";

Fact::Fact(QObject* parent)
    : QObject(parent)
    , _rawValue(0)
    , _type(FactMetaData::valueTypeInt32)
    , _metaData(nullptr)
{
    FactMetaData* metaData = new FactMetaData(_type, this);
    setMetaData(metaData);
}

Fact::Fact(QString name, FactMetaData::ValueType_t type, QObject* parent)
    : QObject(parent)
    , _name(name)
    , _rawValue(0)
    , _type(type)
    , _metaData(nullptr)
{
    FactMetaData* metaData = new FactMetaData(_type, this);
    setMetaData(metaData, true /* setDefaultFromMetaData */);
}

Fact::Fact(FactMetaData* metaData, QObject* parent)
    : QObject(parent)
    , _name(metaData->name())
    , _rawValue(0)
    , _type(metaData->type())
    , _metaData(metaData)
{
    setMetaData(metaData, true /* setDefaultFromMetaData */);
}

QString Fact::validate(const QString& cookedValue, bool convertOnly)
{
    if (_metaData)
    {
        QVariant typedValue;
        QString  errorString;

        _metaData->convertAndValidateCooked(cookedValue, convertOnly, typedValue, errorString);

        return errorString;
    }
    else
    {
        qWarning() << kMissingMetadata << name();
        return QString("Internal error: Meta data pointer missing");
    }
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
    if (_metaData)
    {
        return _metaData->shortDescription();
    }
    else
    {
        qWarning() << kMissingMetadata << name();
        return QString();
    }
}

QString Fact::longDescription() const
{
    if (_metaData)
    {
        return _metaData->longDescription();
    }
    else
    {
        qWarning() << kMissingMetadata << name();
        return QString();
    }
}

int Fact::decimalPlaces() const
{
    if (_metaData)
    {
        return _metaData->decimalPlaces();
    }
    else
    {
        qWarning() << kMissingMetadata << name();
        return FactMetaData::kDefaultDecimalPlaces;
    }
}

QVariant Fact::rawDefaultValue() const
{
    if (_metaData)
    {
        if (!_metaData->defaultValueAvailable())
        {
            qDebug() << "Access to unavailable default value";
        }
        return _metaData->rawDefaultValue();
    }
    else
    {
        qWarning() << kMissingMetadata << name();
        return QVariant(0);
    }
}

QVariant Fact::cookedDefaultValue() const
{
    if (_metaData)
    {
        if (!_metaData->defaultValueAvailable())
        {
            qDebug() << "Access to unavailable default value";
        }
        return _metaData->cookedDefaultValue();
    }
    else
    {
        qWarning() << kMissingMetadata << name();
        return QVariant(0);
    }
}

bool Fact::defaultValueAvailable() const
{
    if (_metaData)
    {
        return _metaData->defaultValueAvailable();
    }
    else
    {
        qWarning() << kMissingMetadata << name();
        return false;
    }
}

QString Fact::cookedDefaultValueString() const
{
    return _variantToString(cookedDefaultValue(), decimalPlaces());
}

QVariant Fact::rawMax() const
{
    if (_metaData)
    {
        return _metaData->rawMax();
    }
    else
    {
        qWarning() << kMissingMetadata << name();
        return QVariant(0);
    }
}

QVariant Fact::cookedMax() const
{
    if (_metaData)
    {
        return _metaData->cookedMax();
    }
    else
    {
        qWarning() << kMissingMetadata << name();
        return QVariant(0);
    }
}

QVariant Fact::cookedMin() const
{
    if (_metaData)
    {
        return _metaData->cookedMin();
    }
    else
    {
        qWarning() << kMissingMetadata << name();
        return QVariant(0);
    }
}

QVariant Fact::rawMin() const
{
    if (_metaData)
    {
        return _metaData->rawMin();
    }
    else
    {
        qWarning() << kMissingMetadata << name();
        return QVariant(0);
    }
}

QString Fact::rawUnits() const
{
    if (_metaData)
    {
        return _metaData->rawUnits();
    }
    else
    {
        qWarning() << kMissingMetadata << name();
        return QString();
    }
}

QString Fact::units() const
{
    if (_metaData)
    {
        return _metaData->cookedUnits();
    }
    else
    {
        qWarning() << kMissingMetadata << name();
        return QString();
    }
}

QVariant Fact::cookedValue() const
{
    if (_metaData)
    {
        return _metaData->defaultTranslator(_rawValue); //默认转换器
    }
    else
    {
        qWarning() << kMissingMetadata << name();
        return _rawValue;
    }
}

QString Fact::rawValueString() const { return _variantToString(rawValue(), decimalPlaces()); }

QString Fact::cookedValueString() const { return _variantToString(cookedValue(), decimalPlaces()); }

QStringList Fact::enumStrings() const
{
    if (_metaData)
    {
        return _metaData->enumStrings();
    }
    else
    {
        qWarning() << kMissingMetadata << name();
        return QStringList();
    }
}

QVariantList Fact::enumValues() const
{
    if (_metaData)
    {
        return _metaData->enumValues();
    }
    else
    {
        qWarning() << kMissingMetadata << name();
        return QVariantList();
    }
}

int Fact::enumIndex()
{
    static const double accuracy = 1.0 / 1000000.0;
    if (_metaData)
    {
        //-- Only enums have an index
        if (_metaData->enumValues().count())
        {
            int index = 0;
            for (QVariant enumValue : _metaData->enumValues())
            {
                if (enumValue == rawValue())
                {
                    return index;
                }
                //-- Float comparissons don't always work
                if (type() == FactMetaData::valueTypeFloat || type() == FactMetaData::valueTypeDouble)
                {
                    double diff = fabs(enumValue.toDouble() - rawValue().toDouble());
                    if (diff < accuracy)
                    {
                        return index;
                    }
                }
                index++;
            }
            // Current value is not in list, add it manually
            _metaData->addEnumInfo(tr("Unknown: %1").arg(rawValue().toString()), rawValue());
            emit enumsChanged();
            return index;
        }
    }
    else
    {
        qWarning() << kMissingMetadata << name();
    }
    return -1;
}

QString Fact::enumStringValue()
{
    if (_metaData)
    {
        int enumIndex = this->enumIndex();
        if (enumIndex >= 0 && enumIndex < _metaData->enumStrings().count())
        {
            return _metaData->enumStrings()[ enumIndex ];
        }
    }
    else
    {
        qWarning() << kMissingMetadata << name();
    }

    return QString();
}

void Fact::setSendValueChangedSignals(bool sendValueChangedSignals)
{
    if (sendValueChangedSignals != _sendValueChangedSignals)
    {
        _sendValueChangedSignals = sendValueChangedSignals;
    }
}

void Fact::_sendValueChangedSignal(QVariant value)
{
    if (_sendValueChangedSignals)
    {
        emit valueChanged(value);
        //qDebug() << "sendValueChangedSignalsChanged";
        _deferredValueChangeSignal = false;
    }
    else
    {
        _deferredValueChangeSignal = true;
    }
}

void Fact::sendDeferredValueChangedSignal(void)
{
    if (_deferredValueChangeSignal)
    {
        _deferredValueChangeSignal = false;
        emit valueChanged(cookedValue());
        //qDebug() << "sendDeferredValueChangedSignal";
    }
}

void Fact::setRawValue(const QVariant& value)
{
    if (_metaData)
    {
        QVariant typedValue;
        QString  errorString;

        if (_metaData->convertAndValidateRaw(value, true /* convertOnly */, typedValue, errorString))
        {
            if (typedValue != _rawValue)
            {
                _rawValue.setValue(typedValue);
                _sendValueChangedSignal(cookedValue());
                //-- Must be in this order
                // emit _containerRawValueChanged(rawValue());
                emit rawValueChanged(_rawValue);
            }
        }
    }
    else
    {
        qWarning() << kMissingMetadata << name();
    }
}

void Fact::setCookedValue(const QVariant& value)
{
    if (_metaData)
    {
        setRawValue(value);
    }
    else
    {
        qWarning() << kMissingMetadata << name();
    }
    //qWarning() << "setCookedValue" << name();
}

void Fact::setMetaData(FactMetaData* metaData, bool setDefaultFromMetaData)
{
    _metaData = metaData;
    if (setDefaultFromMetaData && metaData->defaultValueAvailable())
    {
        setRawValue(rawDefaultValue());
    }
    emit valueChanged(cookedValue());
}

void Fact::setEnumIndex(int index)
{
    if (_metaData)
    {
        setCookedValue(_metaData->enumValues()[ index ]);
    }
    else
    {
        qWarning() << kMissingMetadata << name();
    }
}

void Fact::setEnumStringValue(const QString& value)
{
    int index = valueIndex(value);
    if (index != -1)
    {
        setCookedValue(_metaData->enumValues()[ index ]);
    }
}

int Fact::valueIndex(const QString& value)
{
    if (_metaData)
    {
        return _metaData->enumStrings().indexOf(value);
    }
    qWarning() << kMissingMetadata << name();
    return -1;
}

QString Fact::cookedMaxString() const
{
    return _variantToString(cookedMax(), decimalPlaces());
}

QVariant Fact::cookedMinString() const
{
    return _variantToString(cookedMin(), decimalPlaces());
}

QString Fact::_variantToString(const QVariant& variant, int decimalPlaces) const
{
    QString valueString;

    switch (type())
    {
        case FactMetaData::valueTypeFloat:
        {
            float fValue = variant.toFloat();
            if (qIsNaN(fValue))
            {
                valueString = QStringLiteral("--.--");
            }
            else
            {
                valueString = QString("%1").arg(fValue, 0, 'f', decimalPlaces);
            }
        }
        break;
        case FactMetaData::valueTypeDouble:
        {
            double dValue = variant.toDouble();
            if (qIsNaN(dValue))
            {
                valueString = QStringLiteral("--.--");
            }
            else
            {
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
