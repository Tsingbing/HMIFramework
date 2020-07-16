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
    Fact(QObject *parent = nullptr);
    Fact(QString name, FactMetaData::ValueType_t type, QObject* parent = nullptr);

    QString         name                    (void) const;
    FactMetaData::ValueType_t type          (void) const;
    QString         shortDescription        (void) const;
    QVariant        rawValue                (void) const { return _rawValue; }
    QString         rawValueString          (void) const;
    void setRawValue        (const QVariant& value);
    void setMetaData(FactMetaData* metaData, bool setDefaultFromMetaData = false);

    FactMetaData* metaData() { return _metaData; }

signals:

protected:
    QString _variantToString(const QVariant& variant, int decimalPlaces) const;

    QString                     _name;
    QVariant                    _rawValue;
    FactMetaData::ValueType_t   _type;
    FactMetaData*               _metaData;
};

#endif // FACT_H