#ifndef APPSETTINGS_H
#define APPSETTINGS_H

#include <SettingsGroup.h>

class AppSettings : public SettingsGroup
{
    Q_OBJECT

public:
    AppSettings(QObject* parent = nullptr);
    Q_PROPERTY(Fact* appFontPointSize READ appFontPointSize CONSTANT)
    Q_PROPERTY(Fact* language READ language CONSTANT)
    Q_PROPERTY(Fact* indoorPalette READ indoorPalette CONSTANT)

public:
    Fact*              indoorPalette();
    static const char* indoorPaletteName;
    Fact*              appFontPointSize();
    Fact*              language();

    static const char* name;
    static const char* settingsGroup;
    static const char* appFontPointSizeName;
    static const char* languageName;

private:
    SettingsFact* _appFontPointSizeFact = nullptr;
    SettingsFact* _languageFact         = nullptr;
    SettingsFact* _indoorPaletteFact    = nullptr;

private slots:
    void _languageChanged();
    void _indoorPaletteChanged();
};

#endif // APPSETTINGS_H
