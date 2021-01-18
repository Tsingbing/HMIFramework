#ifndef APPSETTINGS_H
#define APPSETTINGS_H

#include <SettingsGroup.h>

class AppSettings : public SettingsGroup
{
    Q_OBJECT

public:
    AppSettings(QObject* parent = nullptr);

    DEFINE_SETTINGFACT(savePath)

    Q_PROPERTY(Fact* appFontPointSize READ appFontPointSize CONSTANT)
    Q_PROPERTY(Fact* language READ language CONSTANT)
    Q_PROPERTY(Fact* indoorPalette READ indoorPalette CONSTANT)
    Q_PROPERTY(QString crashSavePath READ crashSavePath NOTIFY savePathsChanged)

public:
    Fact*   indoorPalette();
    Fact*   appFontPointSize();
    Fact*   language();
    QString crashSavePath();

    static const char* name;
    static const char* settingsGroup;
    static const char* appFontPointSizeName;
    static const char* indoorPaletteName;
    static const char* languageName;

    // Child directories of savePath for specific file types
    static const char* parameterDirectory;
    static const char* telemetryDirectory;
    static const char* missionDirectory;
    static const char* logDirectory;
    static const char* videoDirectory;
    static const char* crashDirectory;

signals:
    void savePathsChanged();

private:
    SettingsFact* _appFontPointSizeFact = nullptr;
    SettingsFact* _languageFact         = nullptr;
    SettingsFact* _indoorPaletteFact    = nullptr;

private slots:
    void _languageChanged();
    void _checkSavePathDirectories();
    void _indoorPaletteChanged();
};

#endif // APPSETTINGS_H
