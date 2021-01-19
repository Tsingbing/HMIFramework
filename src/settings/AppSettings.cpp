#include "AppSettings.h"
#include "HMIPalette.h"
#include "XApplication.h"
#include <QQmlEngine>
#include <QtQml>

const char* AppSettings::name                 = "App";
const char* AppSettings::settingsGroup        = "";
const char* AppSettings::languageName         = "language";
const char* AppSettings::appFontPointSizeName = "appFontPointSize";
const char* AppSettings::indoorPaletteName    = "indoorPalette";

const char* AppSettings::parameterDirectory = "Parameters";
const char* AppSettings::telemetryDirectory = "Telemetry";
const char* AppSettings::missionDirectory   = "Missions";
const char* AppSettings::logDirectory       = "Logs";
const char* AppSettings::videoDirectory     = "Video";
const char* AppSettings::crashDirectory     = "CrashLogs";

AppSettings::AppSettings(QObject* parent)
    : SettingsGroup(name, settingsGroup, parent)
{
    qmlRegisterUncreatableType<AppSettings>("HMI.SettingsManager", 1, 0, "AppSettings", "Reference only");
    HMIPalette::setGlobalTheme(indoorPalette()->rawValue().toBool() ? HMIPalette::Dark : HMIPalette::Light);

    SettingsFact* savePathFact = qobject_cast<SettingsFact*>(savePath());

    QString appName = XApp()->applicationName();

    bool userHasModifiedSavePath = !savePathFact->rawValue().toString().isEmpty() || !_nameToMetaDataMap[ savePathName ]->rawDefaultValue().toString().isEmpty();

    if (!userHasModifiedSavePath)
    {
        QDir rootDir = QDir(QStandardPaths::writableLocation(QStandardPaths::DocumentsLocation));
        savePathFact->setRawValue(rootDir.filePath(appName));
    }

    connect(savePathFact, &Fact::rawValueChanged, this, &AppSettings::savePathsChanged);
    connect(savePathFact, &Fact::rawValueChanged, this, &AppSettings::_checkSavePathDirectories);

    _checkSavePathDirectories();

    SettingsFact* languageFact = qobject_cast<SettingsFact*>(language());
    connect(languageFact, &Fact::rawValueChanged, this, &AppSettings::_languageChanged);
}

DECLARE_SETTINGSFACT(AppSettings, savePath)

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
        //qDebug() << _languageFact->enumStrings();
    }
    return _languageFact;
}

QString AppSettings::crashSavePath()
{
    QString path = savePath()->rawValue().toString();
    if (!path.isEmpty() && QDir(path).exists())
    {
        QDir dir(path);
        return dir.filePath(crashDirectory);
    }
    return QString();
}

void AppSettings::_languageChanged()
{
    XApp()->setLanguage();
}

void AppSettings::_checkSavePathDirectories()
{
    QDir savePathDir(savePath()->rawValue().toString());
    if (!savePathDir.exists())
    {
        QDir().mkpath(savePathDir.absolutePath());
    }
    if (savePathDir.exists())
    {
        //savePathDir.mkdir(parameterDirectory);
        //savePathDir.mkdir(telemetryDirectory);
        //savePathDir.mkdir(missionDirectory);
        savePathDir.mkdir(logDirectory);
        //savePathDir.mkdir(videoDirectory);
        savePathDir.mkdir(crashDirectory);
    }
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
