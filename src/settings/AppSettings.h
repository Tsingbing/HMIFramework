#ifndef APPSETTINGS_H
#define APPSETTINGS_H

#include <SettingsGroup.h>

class AppSettings : public SettingsGroup
{
    Q_OBJECT

public:
    AppSettings(QObject* parent = nullptr);
    static const char* name;
    static const char* settingsGroup;

private:
    SettingsFact* _languageFact = nullptr;

public:
    Fact* language();
    static const char* languageName;

private slots:
    void _languageChanged();
};

#endif // APPSETTINGS_H
