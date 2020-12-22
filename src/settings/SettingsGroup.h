#ifndef SETTINGSGROUP_H
#define SETTINGSGROUP_H

#include <QObject>
#include "SettingsFact.h"

class SettingsGroup : public QObject
{
    Q_OBJECT
public:
    SettingsGroup(const QString &name, const QString &settingsGroup, QObject* parent = nullptr);

signals:

protected:
    SettingsFact* _createSettingsFact(const QString& factName);
    QString _name;
    QString _settingsGroup;

    QMap<QString, FactMetaData*> _nameToMetaDataMap;
};

#endif // SETTINGSGROUP_H
