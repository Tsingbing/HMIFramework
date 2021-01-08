#ifndef APPSETTINGS_H
#define APPSETTINGS_H

#include <SettingsGroup.h>

class AppSettings : public SettingsGroup
{
    Q_OBJECT

public:
    AppSettings(QObject* parent = nullptr);
    Q_PROPERTY(Fact* appFontPointSize READ appFontPointSize CONSTANT)
    Fact* appFontPointSize();

    static const char* name;
    static const char* settingsGroup;
    static const char* appFontPointSizeName;

private:
    SettingsFact* _appFontPointSizeFact = nullptr;
    SettingsFact* _languageFact         = nullptr;

public:
    Fact*              language();
    static const char* languageName;

private slots:
    void _languageChanged();
};

#endif // APPSETTINGS_H
