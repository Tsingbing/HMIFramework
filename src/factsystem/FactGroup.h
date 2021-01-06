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
    FactGroup(int updateRateMsecs, const QString& metaDataFile, QObject* parent = 0);

    /// @return Fact for specified name, NULL if not found
    Fact*       getFact(const QString& name);
    QStringList factNames(void) const { return _factNames; }

signals:
    void factNamesChanged(void);
    void factGroupNamesChanged(void);

protected:
    int _updateRateMSecs; ///< Fact::valueChanged信号的更新频率，0：立即更新

protected:
    void _addFact(Fact* fact, const QString& name);
    void _loadFromJsonArray(const QJsonArray jsonArray);

protected slots:
    virtual void _updateAllValues(void);

private:
    void   _setupTimer();
    QTimer _updateTimer;

protected:
    QMap<QString, Fact*>         _nameToFactMap;
    QMap<QString, FactMetaData*> _nameToFactMetaDataMap;
    QStringList                  _factNames;
};

#endif // FACTGROUP_H
