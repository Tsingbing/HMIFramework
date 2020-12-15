#include "FactGroup.h"
#include "JsonHelper.h"

#include <QJsonDocument>
#include <QJsonParseError>
#include <QJsonArray>
#include <QDebug>
#include <QFile>

FactGroup::FactGroup(int updateRateMsecs, const QString &metaDataFile, QObject *parent)
    : QObject(parent)
    , _updateRateMSecs(updateRateMsecs)
{
    _setupTimer();
    _nameToFactMetaDataMap = FactMetaData::createMapFromJsonFile(metaDataFile, this);
}

Fact *FactGroup::getFact(const QString &name)
{
    Fact* fact = 0;

    if (_nameToFactMap.contains(name)) {
        fact = _nameToFactMap[name];
    } else {
        qWarning() << "Unknown Fact" << name;
    }

    return fact;
}

void FactGroup::_addFact(Fact *fact, const QString &name)
{
    if (_nameToFactMap.contains(name)) {
        qWarning() << "Duplicate Fact" << name;
        return;
    }

    //fact->setSendValueChangedSignals(_updateRateMSecs == 0);
    if (_nameToFactMetaDataMap.contains(name)) {
        fact->setMetaData(_nameToFactMetaDataMap[name]);
    }
    _nameToFactMap[name] = fact;
    _factNames.append(name);
}

void FactGroup::_loadFromJsonArray(const QJsonArray jsonArray)
{
    QMap<QString, QString> defineMap;
    _nameToFactMetaDataMap = FactMetaData::createMapFromJsonArray(jsonArray, defineMap, this);
}

void FactGroup::_updateAllValues()
{
    for(Fact* fact: _nameToFactMap) {
        //fact->sendDeferredValueChangedSignal();
        emit fact->valueChanged();
    }
}

void FactGroup::_setupTimer()
{
    if (_updateRateMSecs > 0) {
        connect(&_updateTimer, &QTimer::timeout, this, &FactGroup::_updateAllValues);
        _updateTimer.setSingleShot(false);
        _updateTimer.setInterval(_updateRateMSecs);
        _updateTimer.start();
    }
}
