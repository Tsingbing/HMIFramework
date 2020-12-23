/****************************************************************************
 *
 * (c) 2009-2020 QGROUNDCONTROL PROJECT <http://www.qgroundcontrol.org>
 *
 * QGroundControl is licensed according to the terms in the file
 * COPYING.md in the root of the source code directory.
 *
 ****************************************************************************/

#ifndef JsonHelper_H
#define JsonHelper_H

#include <QJsonObject>
#include <QVariantList>

/// @brief Json manipulation helper class.
/// Primarily used for parsing and processing Fact metadata.
class JsonHelper
{
public:
    /// Determines is the specified data is a json file
    /// @return true: file is json, false: file is not json
    static bool isJsonFile(const QByteArray& bytes,   ///< json bytes
                           QJsonDocument&    jsonDoc, ///< returned json document
                           QString&          errorString);     ///< error on parse failure

    /// Saves the standard file header the json object
    static void saveQGCJsonFileHeader(QJsonObject&   jsonObject, ///< root json object
                                      const QString& fileType,   ///< file type for file
                                      int            version);              ///< version number for file

    /// Validates the standard parts of a QGC json file:
    ///     jsonFileTypeKey - Required and checked to be equal to expectedFileType
    ///     jsonVersionKey - Required and checked to be below supportedMajorVersion, supportedMinorVersion
    ///     jsonGroundStationKey - Required and checked to be string type
    /// @return false: validation failed, errorString set
    static bool validateQGCJsonFile(const QJsonObject& jsonObject,          ///< json object to validate
                                    const QString&     expectedFileType,    ///< correct file type for file
                                    int                minSupportedVersion, ///< minimum supported version
                                    int                maxSupportedVersion, ///< maximum supported major version
                                    int&               version,             ///< returned file version
                                    QString&           errorString);                  ///< returned error string if validation fails

    /// Validates that the specified keys are in the object
    /// @return false: validation failed, errorString set
    static bool validateRequiredKeys(const QJsonObject& jsonObject, ///< json object to validate
                                     const QStringList& keys,       ///< keys which are required to be present
                                     QString&           errorString);         ///< returned error string if validation fails

    /// Validates the types of specified keys are in the object
    /// @return false: validation failed, errorString set
    static bool validateKeyTypes(const QJsonObject&             jsonObject, ///< json object to validate
                                 const QStringList&             keys,       ///< keys to validate
                                 const QList<QJsonValue::Type>& types,      ///< required type for each key, QJsonValue::Null specifies double with possible NaN
                                 QString&                       errorString);                     ///< returned error string if validation fails

    typedef struct
    {
        const char*      key;      ///< json key name
        QJsonValue::Type type;     ///< required type for key, QJsonValue::Null specifies double with possible NaN
        bool             required; ///< true: key must be present
    } KeyValidateInfo;

    static bool validateKeys(const QJsonObject& jsonObject, const QList<KeyValidateInfo>& keyInfo, QString& errorString);

    static bool parseEnum(const QJsonObject& jsonObject, QStringList& enumStrings, QStringList& enumValues, QString& errorString, QString valueName = QString());
    static bool parseEnum(const QJsonObject& jsonObject, QMap<QString, QString>& defineMap, QStringList& enumStrings, QStringList& enumValues, QString& errorString, QString valueName = QString());

    /// Returns NaN if the value is null, or if not, the double value
    static double possibleNaNJsonValue(const QJsonValue& value);

    static const char* jsonVersionKey;
    static const char* jsonGroundStationKey;
    static const char* jsonGroundStationValue;
    static const char* jsonFileTypeKey;

private:
    static QString _jsonValueTypeToString(QJsonValue::Type type);

    static bool _parseEnumWorker(const QJsonObject& jsonObject, QMap<QString, QString>& defineMap, QStringList& enumStrings, QStringList& enumValues, QString& errorString, QString valueName);

    static const char* _enumStringsJsonKey;
    static const char* _enumValuesJsonKey;
};

#endif
