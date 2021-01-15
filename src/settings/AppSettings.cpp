#include "AppSettings.h"
#include "HMIPalette.h"
#include <QQmlEngine>
#include <QtQml>

const char* AppSettings::name                 = "App";
const char* AppSettings::settingsGroup        = "";
const char* AppSettings::languageName         = "language";
const char* AppSettings::appFontPointSizeName = "appFontPointSize";
const char* AppSettings::indoorPaletteName    = "indoorPalette";

AppSettings::AppSettings(QObject* parent)
    : SettingsGroup(name, settingsGroup, parent)
{
    qmlRegisterUncreatableType<AppSettings>("HMI.SettingsManager", 1, 0, "AppSettings", "Reference only");
    HMIPalette::setGlobalTheme(indoorPalette()->rawValue().toBool() ? HMIPalette::Dark : HMIPalette::Light);
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
        qDebug() << _languageFact->enumStrings();
    }
    return _languageFact;
}

void AppSettings::_languageChanged()
{
}

void AppSettings::_indoorPaletteChanged()
{
    HMIPalette::setGlobalTheme(indoorPalette()->rawValue().toBool() ? HMIPalette::Dark : HMIPalette::Light);
}

Fact* AppSettings::indoorPalette()
{
    if (!_indoorPaletteFact)
    {
        _indoorPaletteFact = _createSettingsFact(indoorPaletteName);
        connect(_indoorPaletteFact, &Fact::rawValueChanged, this, &AppSettings::_indoorPaletteChanged);
    }
    return _indoorPaletteFact;
}
