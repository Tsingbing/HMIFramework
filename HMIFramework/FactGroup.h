#ifndef FACTGROUP_H
#define FACTGROUP_H

#include <QObject>

#include "Fact.h"
#include <QMap>
#include <QTimer>

class FactGroup : public QObject
{
    Q_OBJECT
public:
    FactGroup(int updateRateMsecs, const QString& metaDataFile, QObject* parent = nullptr);

signals:

protected:
    int _updateRateMSecs;

protected:
    void _addFact(Fact* fact, const QString& name);

protected slots:
    virtual void _updateAllValues(void);

private:
    void _setupTimer();
    QTimer _updateTimer;

protected:
    QMap<QString, Fact*>            _nameToFactMap;
    QStringList                     _factNames;
};

#endif // FACTGROUP_H
