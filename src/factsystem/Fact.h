#ifndef FACT_H
#define FACT_H

#include "FactMetaData.h"
#include <QObject>
#include <QString>
#include <QVariant>
#include <cmath>

class Fact : public QObject
{
    Q_OBJECT
    QString m_maxString;

    QVariant m_minString;

public:
    Fact(QObject* parent = nullptr);
    Fact(QString name, FactMetaData::ValueType_t type, QObject* parent = nullptr);

    /// Creates a Fact using the name and type from metaData.
    Fact(FactMetaData* metaData, QObject* parent = nullptr);

    Q_PROPERTY(QString name READ name CONSTANT)
    Q_PROPERTY(QString shortDescription READ shortDescription CONSTANT)
    Q_PROPERTY(QString longDescription READ longDescription CONSTANT)
    Q_PROPERTY(QString units READ units CONSTANT)
    Q_PROPERTY(QString valueString READ cookedValueString NOTIFY valueChanged)
    Q_PROPERTY(QVariant value READ cookedValue WRITE setCookedValue NOTIFY valueChanged)
    Q_PROPERTY(QVariant rawValue READ rawValue WRITE setRawValue NOTIFY rawValueChanged)
    Q_PROPERTY(QVariant max READ cookedMax CONSTANT)
    Q_PROPERTY(QString maxString READ cookedMaxString CONSTANT)
    Q_PROPERTY(QVariant min READ cookedMin CONSTANT)
    Q_PROPERTY(QVariant minString READ cookedMinString CONSTANT)
    Q_PROPERTY(QVariant defaultValue READ cookedDefaultValue CONSTANT)
    Q_PROPERTY(QString defaultValueString READ cookedDefaultValueString CONSTANT)
    Q_PROPERTY(bool defaultValueAvailable READ defaultValueAvailable CONSTANT)

    Q_PROPERTY(int enumIndex READ enumIndex WRITE setEnumIndex NOTIFY valueChanged)
    Q_PROPERTY(QStringList enumStrings READ enumStrings NOTIFY enumsChanged)
    Q_PROPERTY(QString enumStringValue READ enumStringValue WRITE setEnumStringValue NOTIFY valueChanged)
    Q_PROPERTY(QVariantList enumValues READ enumValues NOTIFY enumsChanged)
    Q_PROPERTY(QStringList bitmaskStrings READ bitmaskStrings NOTIFY bitmaskStringsChanged)
    Q_PROPERTY(QVariantList bitmaskValues READ bitmaskValues NOTIFY bitmaskValuesChanged)

    /// @brief Convert and validate value
    /// @param cookedValue: Value to convert and validate
    /// @param convertOnly true: validate type conversion only, false: validate against meta data as well
    Q_INVOKABLE QString validate(const QString& cookedValue, bool convertOnly);

    QString                   name(void) const;
    FactMetaData::ValueType_t type(void) const;
    QString                   shortDescription(void) const;
    QString                   longDescription(void) const;
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
    int                       enumIndex();
    QString                   enumStringValue(void); // This is not const, since an unknown value can modify the enum lists
    QStringList               bitmaskStrings(void) const;
    QVariantList              bitmaskValues(void) const;
    QString                   cookedMaxString() const;
    QVariant                  cookedMinString() const;

    void setRawValue(const QVariant& value);
    void setCookedValue(const QVariant& value);
    void setEnumIndex(int enumIndex);
    void setEnumStringValue(const QString& value);
    int  valueIndex(const QString& value);

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

public slots:

signals:
    void enumsChanged(void);
    void bitmaskStringsChanged(void);
    void bitmaskValuesChanged(void);
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
