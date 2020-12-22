#ifndef SETTINGSFACT_H
#define SETTINGSFACT_H

#include "Fact.h"

class SettingsFact : public Fact
{
    Q_OBJECT

public:
    SettingsFact(QObject* parent = nullptr);
    SettingsFact(QString settingsGroup, FactMetaData* metaData, QObject* parent = nullptr);

private slots:
    void _rawValueChanged(QVariant value);

private:
    QString _settingsGroup;
};

#endif // SETTINGFACT_H
