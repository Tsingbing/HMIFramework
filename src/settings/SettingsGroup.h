#ifndef SETTINGSGROUP_H
#define SETTINGSGROUP_H

#include <QObject>

class SettingsGroup : public QObject
{
    Q_OBJECT
public:
    explicit SettingsGroup(QObject *parent = 0);

signals:
};

#endif // SETTINGSGROUP_H
