#include "AppSettings.h"
#include <QQmlEngine>
#include <QtQml>

const char* AppSettings::name                 = "App";
const char* AppSettings::settingsGroup        = "";
const char* AppSettings::languageName         = "language";
const char* AppSettings::appFontPointSizeName = "appFontPointSize";

AppSettings::AppSettings(QObject* parent)
    : SettingsGroup(name, settingsGroup, parent)
{
    qmlRegisterUncreatableType<AppSettings>("HMI.SettingsManager", 1, 0, "AppSettings", "Reference only");

    SettingsFact* languageFact = qobject_cast<SettingsFact*>(language());
    connect(languageFact, &Fact::rawValueChanged, this, &AppSettings::_languageChanged);
}

Fact* AppSettings::appFontPointSize()
{
    if (!_appFontPointSizeFact)
    {
        _appFontPointSizeFact = _createSettingsFact(appFontPointSizeName);
    }
    return _appFontPointSizeFact;
}

Fact* AppSettings::language()
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
