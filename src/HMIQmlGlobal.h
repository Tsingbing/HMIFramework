#ifndef HMIQMLGLOBAL_H
#define HMIQMLGLOBAL_H

#include "HMILoggingCategory.h"
#include "SettingsManager.h"
#include "Tool.h"
#include "Toolbox.h"
#include "VehicleManager.h"
#include "XApplication.h"
#include <QObject>

class HMIQmlGlobal : public Tool
{
    Q_OBJECT
public:
    HMIQmlGlobal(XApplication* app, Toolbox* toolbox);
    ~HMIQmlGlobal();

    Q_PROPERTY(VehicleManager* vehicleManager READ vehicleManager CONSTANT)
    Q_PROPERTY(SettingsManager* settingsManager READ settingsManager CONSTANT)
    Q_PROPERTY(QString appName READ appName CONSTANT)
    Q_PROPERTY(QString hmiVersion READ hmiVersion CONSTANT)
    Q_PROPERTY(qreal zOrderTopMost READ zOrderTopMost CONSTANT) ///< z order for top most items, toolbar, main window sub view

    /// Returns the list of available logging category names.
    Q_INVOKABLE QStringList loggingCategories(void) const { return HMILoggingCategoryRegister::instance()->registeredCategories(); }

    /// Turns on/off logging for the specified category. State is saved in app settings.
    Q_INVOKABLE void setCategoryLoggingOn(const QString& category, bool enable) { HMILoggingCategoryRegister::instance()->setCategoryLoggingOn(category, enable); }

    /// Returns true if logging is turned on for the specified category.
    Q_INVOKABLE bool categoryLoggingOn(const QString& category) { return HMILoggingCategoryRegister::instance()->categoryLoggingOn(category); }

    /// Updates the logging filter rules after settings have changed
    Q_INVOKABLE void updateLoggingFilterRules(void) { HMILoggingCategoryRegister::instance()->setFilterRulesFromSettings(QString()); }

    // Property accesors
    QString          appName() { return XApp()->applicationName(); }
    VehicleManager*  vehicleManager() { return _vehicleManager; }
    SettingsManager* settingsManager() { return _settingsManager; }
    // Overrides from Tool
    virtual void setToolbox(Toolbox* toolbox);

    qreal zOrderTopMost() const { return 1000; }

    QString hmiVersion() const
    {
        QString versionStr = XApp()->applicationVersion();
        return versionStr;
    }

private:
    VehicleManager*  _vehicleManager  = nullptr;
    SettingsManager* _settingsManager = nullptr;
};

#endif // HMIQMLGLOBAL_H
