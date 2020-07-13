#include "Fact.h"

Fact::Fact(QObject *parent)
    : QObject(parent)
    , _metaData(nullptr)
{

}

Fact::Fact(QString name, FactMetaData::ValueType_t type, QObject *parent)
    : QObject(parent)
    , _name(name)
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

QString Fact::shortDescription() const
{
//    if (_metaData) {
//        return _metaData->shortDescription();
//    } else {
//        qWarning() << kMissingMetadata << name();
//        return QString();
//    }
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
