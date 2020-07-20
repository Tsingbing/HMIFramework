#ifndef FACTMETADATA_H
#define FACTMETADATA_H

#include <QObject>
#include <QString>
#include <QVariant>

///保存与Fact关联的元数据。
///保存与Fact关联的元数据。
///因为同一个Fact可能有多个实例，所以它被保存在与Fact本身不同的对象中。但是只有一个FactMetaData实例或每个Fact
///这FactMetaData与每个fact都有关联。它提供了Fact的详细信息，以推动自动用户界面的生成和验证
class FactMetaData : public QObject
{
    Q_OBJECT

public:
    typedef enum {
        valueTypeUint8,
        valueTypeInt8,
        valueTypeUint16,
        valueTypeInt16,
        valueTypeUint32,
        valueTypeInt32,
        valueTypeUint64,
        valueTypeInt64,
        valueTypeFloat,
        valueTypeDouble,
        valueTypeString,
        valueTypeBool,
    } ValueType_t;

    FactMetaData(FactMetaData::ValueType_t type, const QString name, QObject *parent);

    ValueType_t     type                    (void) const { return _type; }
    QString         name                    (void) const { return _name; }
    QString         shortDescription        (void) const { return _shortDescription; }
    QString         rawUnits                (void) const { return _rawUnits; }
    QVariant        rawMax                  (void) const { return _rawMax; }
    QVariant        rawMin                  (void) const { return _rawMin; }
    int             decimalPlaces           (void) const;
    QVariant        rawDefaultValue         (void) const;

    void setName                    (const QString& name)               { _name = name; }
    void setShortDescription        (const QString& shortDescription)   { _shortDescription = shortDescription; }
    void setRawUnits                (const QString& rawUnits)           { _rawUnits = rawUnits; }
    void setRawMax                  (const QVariant& rawMax);
    void setRawMin                  (const QVariant& rawMin);
    void setDecimalPlaces           (int decimalPlaces)                 { _decimalPlaces = decimalPlaces; }
    void setRawDefaultValue         (const QVariant& rawDefaultValue);

    static const int kDefaultDecimalPlaces = 3;  ///< Default value for decimal places if not specified/known
    static const int kUnknownDecimalPlaces = -1; ///< Number of decimal places to specify is not known

private:
    QVariant _minForType(void) const;
    QVariant _maxForType(void) const;

    ValueType_t     _type;                  ///< must be first for correct constructor init
    QString         _name;                  ///< 名称
    QString         _shortDescription;      ///< 简介
    QString         _rawUnits;              ///< 原始值单位
    QVariant        _rawMax;                ///< 原始值最大值
    QVariant        _rawMin;                ///< 原始值最小值
    int             _decimalPlaces;         ///< 小数点位数
    QVariant        _rawDefaultValue;       ///< 默认原始值

    static const char* _typeJsonKey;
    static const char* _nameJsonKey;
    static const char* _shortDescriptionJsonKey;
    static const char* _unitsJsonKey;
    static const char* _minJsonKey;
    static const char* _maxJsonKey;
    static const char* _decimalPlacesJsonKey;
    static const char* _defaultValueJsonKey;

};

#endif // FACTMETADATA_H
