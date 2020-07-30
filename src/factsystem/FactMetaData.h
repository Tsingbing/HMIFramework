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

    FactMetaData(ValueType_t type, QObject* parent = nullptr);
    FactMetaData(FactMetaData::ValueType_t type, const QString name, QObject *parent);

    static QMap<QString, FactMetaData*> createMapFromJsonFile(const QString& jsonFilename, QObject* metaDataParent);
    static QMap<QString, FactMetaData*> createMapFromJsonArray(const QJsonArray jsonArray, QMap<QString, QString>& defineMap, QObject* metaDataParent);

    static FactMetaData* createFromJsonObject(const QJsonObject& json, QMap<QString, QString>& defineMap, QObject* metaDataParent);

    ValueType_t     type                    (void) const { return _type; }
    QString         name                    (void) const { return _name; }
    QString         shortDescription        (void) const { return _shortDescription; }
    QString         rawUnits                (void) const { return _rawUnits; }
    QVariant        rawMax                  (void) const { return _rawMax; }
    QVariant        rawMin                  (void) const { return _rawMin; }
    int             decimalPlaces           (void) const;
    QVariant        rawDefaultValue         (void) const;
    QVariant        cookedDefaultValue      (void) const { return defaultTranslator(rawDefaultValue()); }
    QString         cookedUnits             (void) const { return rawUnits(); }


    void setName                    (const QString& name)               { _name = name; }
    void setShortDescription        (const QString& shortDescription)   { _shortDescription = shortDescription; }
    void setRawUnits                (const QString& rawUnits)           { _rawUnits = rawUnits; }
    void setRawMax                  (const QVariant& rawMax);
    void setRawMin                  (const QVariant& rawMin);
    void setDecimalPlaces           (int decimalPlaces)                 { _decimalPlaces = decimalPlaces; }
    void setRawDefaultValue         (const QVariant& rawDefaultValue);

    /// 转换和校验数据
    ///     @参数 rawValue: 要转换的值，可以是字符串
    ///     @参数 convertOnly: true：仅转换为正确的类型，不针对元数据进行验证
    ///     @参数 typeValue: 转换后的值
    ///     @参数 errorString: 如果转换失败，将显示错误字符串，因为用户可见，所以值是处理后的值
    /// @returns false：转换失败，赋值errorString
    bool convertAndValidateRaw(const QVariant& rawValue, bool convertOnly, QVariant& typedValue, QString& errorString);

    static const int kDefaultDecimalPlaces = 3;     ///< Default value for decimal places if not specified/known
    static const int kUnknownDecimalPlaces = -1;    ///< Number of decimal places to specify is not known

    static ValueType_t stringToType(const QString& typeString, bool& unknownType);

    ///< translators 是转换rawvalue和cookedvalue（待实现）
    /// 例如：英寸转米 feetToMeters（rawvalue是英寸，cookedvalue是米）
    ///
    /// 内置转换器（默认是不转换）
    static QVariant defaultTranslator(const QVariant& from) { return from; }

private:
    QVariant _minForType(void) const;   ///< 类型最小值
    QVariant _maxForType(void) const;   ///< 类型最小值


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
