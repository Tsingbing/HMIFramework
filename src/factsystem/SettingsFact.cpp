#include "SettingsFact.h"
#include <QDebug>
#include <QSettings>

SettingsFact::SettingsFact(QObject *parent)
    : Fact(parent)
{
}

SettingsFact::SettingsFact(QString settingsGroup, FactMetaData *metaData, QObject *parent)
    : Fact(metaData->name(), metaData->type(), parent)
    , _settingsGroup(settingsGroup)
{
    QSettings settings;
    if (!_settingsGroup.isEmpty())
    {
        settings.beginGroup(_settingsGroup);
    }

    setMetaData(metaData);

    bool _visible = true;

    if (metaData->defaultValueAvailable())
    {
        QVariant rawDefaultValue = metaData->rawDefaultValue();

        if (_visible)
        {
            QVariant typedValue;
            QString  errorString;
            metaData->convertAndValidateRaw(settings.value(_name, rawDefaultValue), true /* conertOnly */, typedValue, errorString);
            _rawValue = typedValue;
        }
        else
        {
            // Setting is not visible, force to default value always
            settings.setValue(_name, rawDefaultValue);
            _rawValue = rawDefaultValue;
        }
    }

    connect(this, &Fact::rawValueChanged, this, &SettingsFact::_rawValueChanged);
}

void SettingsFact::_rawValueChanged(QVariant value)
{
    QSettings settings;

    if (!_settingsGroup.isEmpty())
    {
        settings.beginGroup(_settingsGroup);
    }

    settings.setValue(_name, value);

    qDebug() << "SettingsFact::_rawValueChanged";
}
