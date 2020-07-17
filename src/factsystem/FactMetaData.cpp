#include "FactMetaData.h"

FactMetaData::FactMetaData(QObject *parent) : QObject(parent)
{

}

FactMetaData::FactMetaData(FactMetaData::ValueType_t type, QObject *parent)
    : QObject(parent)
    , _type(type)
{

}
