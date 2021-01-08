#ifndef SETTINGSGROUP_H
#define SETTINGSGROUP_H

#include "SettingsFact.h"
#include <QObject>

#define DECLARE_SETTINGSFACT(CLASS, NAME)                    \
    const char* CLASS::NAME##Name = #NAME;                   \
    Fact*       CLASS::NAME()                                \
    {                                                        \
        if (!_##NAME##Fact)                                  \
        {                                                    \
            _##NAME##Fact = _createSettingsFact(NAME##Name); \
        }                                                    \
        return _##NAME##Fact;                                \
    }

#define DEFINE_SETTINGFACT(NAME)              \
private:                                      \
    SettingsFact* _##NAME##Fact = nullptr;    \
                                              \
public:                                       \
    Q_PROPERTY(Fact* NAME READ NAME CONSTANT) \
    Fact*              NAME();                \
    static const char* NAME##Name;

class SettingsGroup : public QObject
{
    Q_OBJECT
public:
    SettingsGroup(const QString& name, const QString& settingsGroup, QObject* parent = nullptr);

signals:

protected:
    SettingsFact* _createSettingsFact(const QString& factName);
    QString       _name;
    QString       _settingsGroup;

    QMap<QString, FactMetaData*> _nameToMetaDataMap;
};

#endif // SETTINGSGROUP_H
