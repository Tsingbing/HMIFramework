#ifndef FACT_H
#define FACT_H

#include "FactMetaData.h"

#include <QObject>
#include <QString>
#include <QVariant>

class Fact : public QObject
{
    Q_OBJECT
public:
    Fact(QObject* parent = nullptr);
    Fact(QString name, FactMetaData::ValueType_t type, QObject* parent = nullptr);

    /// Creates a Fact using the name and type from metaData.
    Fact(FactMetaData* metaData, QObject* parent = nullptr);

    Q_PROPERTY(QString name READ name CONSTANT)
    Q_PROPERTY(QString shortDescription READ shortDescription CONSTANT)
    Q_PROPERTY(QString valueString READ cookedValueString NOTIFY valueChanged)
    Q_PROPERTY(QVariant value READ cookedValue WRITE setCookedValue NOTIFY valueChanged)
    Q_PROPERTY(QVariant rawValue READ rawValue WRITE setRawValue NOTIFY rawValueChanged)
    Q_PROPERTY(QVariant max READ cookedMax CONSTANT)
    Q_PROPERTY(QVariant min READ cookedMin CONSTANT)
    Q_PROPERTY(QVariant defaultValue READ cookedDefaultValue CONSTANT)
    Q_PROPERTY(QString defaultValueString READ cookedDefaultValueString CONSTANT)

    QString                   name(void) const;
    FactMetaData::ValueType_t type(void) const;
    QString                   shortDescription(void) const;
    int                       decimalPlaces(void) const;
    QVariant                  rawDefaultValue(void) const;
    QVariant                  cookedDefaultValue(void) const;
    bool                      defaultValueAvailable(void) const;
    QString                   cookedDefaultValueString(void) const;
    QVariant                  rawMax(void) const;
    QVariant                  cookedMax(void) const;
    QVariant                  cookedMin(void) const;
    QVariant                  rawMin(void) const;
    QString                   rawUnits(void) const;
    QString                   units(void) const;
    QVariant                  rawValue(void) const { return _rawValue; }
    QVariant                  cookedValue(void) const; /// 转换处理之后的值
    QString                   rawValueString(void) const;
    QString                   cookedValueString(void) const;
    QStringList               enumStrings(void) const;
    QVariantList              enumValues(void) const;

    void setRawValue(const QVariant& value);
    void setCookedValue(const QVariant& value);

    // The following methods allow you to defer sending of the valueChanged signals in order to
    // implement rate limited signalling for ui performance. Used by FactGroup for example.

    void setSendValueChangedSignals(bool sendValueChangedSignals);
    bool sendValueChangedSignals(void) const { return _sendValueChangedSignals; }
    bool deferredValueChangeSignal(void) const { return _deferredValueChangeSignal; }
    void clearDeferredValueChangeSignal(void) { _deferredValueChangeSignal = false; }
    void sendDeferredValueChangedSignal(void);

    /// 设置与Fact相关的元数据
    ///     @参数 metaData FactMetaData for Fact
    ///     @参数 setDefaultFromMetaData true: set the fact value to the default specified in the meta data
    void setMetaData(FactMetaData* metaData, bool setDefaultFromMetaData = false);

    FactMetaData* metaData() { return _metaData; }

signals:
    void valueChanged(QVariant value);
    void rawValueChanged(QVariant value);
    void sendValueChangedSignalsChanged(bool sendValueChangedSignals);

protected:
    QString _variantToString(const QVariant& variant, int decimalPlaces) const;
    void    _sendValueChangedSignal(QVariant value);

    QString                   _name;
    QVariant                  _rawValue;
    bool                      _sendValueChangedSignals;
    bool                      _deferredValueChangeSignal;
    FactMetaData::ValueType_t _type;
    FactMetaData*             _metaData;
};

#endif // FACT_H
