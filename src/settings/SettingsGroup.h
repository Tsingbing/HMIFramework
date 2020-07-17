#ifndef SETTINGSGROUP_H
#define SETTINGSGROUP_H

#include <QObject>

class SettingsGroup : public QObject
{
    Q_OBJECT
public:
    explicit SettingsGroup(QObject *parent = nullptr);

signals:

};

#endif // SETTINGSGROUP_H
