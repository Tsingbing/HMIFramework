#ifndef FACTMETADATA_H
#define FACTMETADATA_H

#include <QObject>
#include <QWidget>

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
        valueTypeElapsedTimeInSeconds,  // Internally stored as double, valueString displays as HH:MM:SS
        valueTypeCustom,                // Internally stored as a QByteArray
    } ValueType_t;

    explicit FactMetaData(QObject *parent = nullptr);
    FactMetaData(ValueType_t type, QObject* parent = nullptr);
    QString         name                    (void) const { return _name; }
    QString         shortDescription        (void) const { return _shortDescription; }

    void setName                    (const QString& name)               { _name = name; }
    void setShortDescription        (const QString& shortDescription)   { _shortDescription = shortDescription; }

signals:

private:
    ValueType_t     _type;                  // must be first for correct constructor init

    QString         _name;
    QString         _shortDescription;
};

#endif // FACTMETADATA_H
