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
    typedef enum
    {
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

    FactMetaData(QObject* parent = nullptr);
    FactMetaData(ValueType_t type, QObject* parent = 0);
    FactMetaData(FactMetaData::ValueType_t type, const QString name, QObject* parent);

    typedef QMap<QString, QString> DefineMap_t;

    static QMap<QString, FactMetaData*> createMapFromJsonFile(const QString& jsonFilename, QObject* metaDataParent);
    static QMap<QString, FactMetaData*> createMapFromJsonArray(const QJsonArray jsonArray, QMap<QString, QString>& defineMap, QObject* metaDataParent);

    static FactMetaData* createFromJsonObject(const QJsonObject& json, QMap<QString, QString>& defineMap, QObject* metaDataParent);

    ValueType_t type(void) const { return _type; }
    QString     name(void) const { return _name; }
    QString     shortDescription(void) const { return _shortDescription; }
    QString     longDescription(void) const { return _longDescription; }
    QString     rawUnits(void) const { return _rawUnits; }
    QVariant    rawMax(void) const { return _rawMax; }
    QVariant    rawMin(void) const { return _rawMin; }
    QVariant    cookedMax(void) const;
    QVariant    cookedMin(void) const;

    int          decimalPlaces(void) const;
    QVariant     rawDefaultValue(void) const;
    QVariant     cookedDefaultValue(void) const { return defaultTranslator(rawDefaultValue()); }
    bool         defaultValueAvailable(void) const { return _defaultValueAvailable; }
    QString      cookedUnits(void) const { return rawUnits(); }
    QStringList  enumStrings(void) const { return _enumStrings; }
    QVariantList enumValues(void) const { return _enumValues; }
    QStringList  bitmaskStrings(void) const { return _bitmaskStrings; }
    QVariantList bitmaskValues(void) const { return _bitmaskValues; }

    /// Used to add new values to the bitmask lists after the meta data has been loaded
    void addBitmaskInfo(const QString& name, const QVariant& value);

    /// Used to add new values to the enum lists after the meta data has been loaded
    void addEnumInfo(const QString& name, const QVariant& value);
    void setName(const QString& name) { _name = name; }
    void setShortDescription(const QString& shortDescription) { _shortDescription = shortDescription; }
    void setLongDescription(const QString& longDescription) { _longDescription = longDescription; }
    void setRawUnits(const QString& rawUnits) { _rawUnits = rawUnits; }
    void setRawMax(const QVariant& rawMax);
    void setRawMin(const QVariant& rawMin);
    void setDecimalPlaces(int decimalPlaces) { _decimalPlaces = decimalPlaces; }
    void setRawDefaultValue(const QVariant& rawDefaultValue);

    bool convertAndValidateRaw(const QVariant& rawValue, bool convertOnly, QVariant& typedValue, QString& errorString);

    /// Same as convertAndValidateRaw except for cookedValue input
    bool convertAndValidateCooked(const QVariant& cookedValue, bool convertOnly, QVariant& typedValue, QString& errorString);

    static const int kDefaultDecimalPlaces = 3;  ///< Default value for decimal places if not specified/known
    static const int kUnknownDecimalPlaces = -1; ///< Number of decimal places to specify is not known

    static ValueType_t stringToType(const QString& typeString, bool& unknownType);

    ///< translators 是转换rawvalue和cookedvalue（待实现）
    /// 例如：英寸转米 feetToMeters（rawvalue是英寸，cookedvalue是米）
    ///
    /// 内置转换器（默认是不转换）
    static QVariant defaultTranslator(const QVariant& from) { return from; }

private:
    QVariant _minForType(void) const; ///< 类型最小值
    QVariant _maxForType(void) const; ///< 类型最小值

    static bool _parseEnum(const QJsonObject& jsonObject, DefineMap_t defineMap, QStringList& rgDescriptions, QStringList& rgValues, QString& errorString);
    static bool _parseValuesArray(const QJsonObject& jsonObject, QStringList& rgDescriptions, QList<double>& rgValues, QString& errorString);
    static bool _parseBitmaskArray(const QJsonObject& jsonObject, QStringList& rgDescriptions, QList<double>& rgValues, QString& errorString);

    static void _loadJsonDefines(const QJsonObject& jsonDefinesObject, QMap<QString, QString>& defineMap);

    ValueType_t  _type;                  ///< must be first for correct constructor init
    QString      _name;                  ///< 名称
    QString      _shortDescription;      ///< 简介
    QString      _longDescription;       ///< 详细介绍
    QString      _rawUnits;              ///< 原始值单位
    QVariant     _rawMax;                ///< 原始值最大值
    QVariant     _rawMin;                ///< 原始值最小值
    int          _decimalPlaces;         ///< 小数点位数
    QVariant     _rawDefaultValue;       ///< 默认原始值
    bool         _defaultValueAvailable; ///< 可获取默认值
    QStringList  _enumStrings;
    QVariantList _enumValues;
    QStringList  _bitmaskStrings;
    QVariantList _bitmaskValues;

    static const char* _typeJsonKey;
    static const char* _nameJsonKey;
    static const char* _shortDescriptionJsonKey;
    static const char* _longDescriptionJsonKey;
    static const char* _unitsJsonKey;
    static const char* _minJsonKey;
    static const char* _maxJsonKey;
    static const char* _decimalPlacesJsonKey;
    static const char* _defaultValueJsonKey;
    static const char* _enumStringsJsonKey;
    static const char* _enumValuesJsonKey;

    static const char* _enumValuesArrayJsonKey;
    static const char* _enumBitmaskArrayJsonKey;
    static const char* _enumValuesArrayValueJsonKey;
    static const char* _enumValuesArrayDescriptionJsonKey;
    static const char* _enumBitmaskArrayIndexJsonKey;
    static const char* _enumBitmaskArrayDescriptionJsonKey;

    static const char* _jsonMetaDataDefinesName;
    static const char* _jsonMetaDataFactsName;
};

#endif // FACTMETADATA_H
