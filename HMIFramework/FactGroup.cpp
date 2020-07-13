#include "FactGroup.h"

FactGroup::FactGroup(int updateRateMsecs, const QString &metaDataFile, QObject *parent)
    : QObject(parent)
    , _updateRateMSecs(updateRateMsecs)
{

}

void FactGroup::_updateAllValues()
{
//    for(Fact* fact: _nameToFactMap) {
//        fact->sendDeferredValueChangedSignal();
//    }
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
