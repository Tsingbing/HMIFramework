#include "AppSettings.h"

const char *AppSettings::name          = "App";
const char *AppSettings::settingsGroup = "";
const char *AppSettings::languageName  = "language";

AppSettings::AppSettings(QObject *parent)
    : SettingsGroup(name, settingsGroup, parent)
{
    SettingsFact *languageFact = qobject_cast<SettingsFact *>(language());
    connect(languageFact, &Fact::rawValueChanged, this, &AppSettings::_languageChanged);
}

Fact *AppSettings::language()
{
    if (!_languageFact)
    {
        _languageFact = _createSettingsFact(languageName);
    }
    return _languageFact;
}

void AppSettings::_languageChanged()
{
}
