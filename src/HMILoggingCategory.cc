/****************************************************************************
 *
 * (c) 2009-2020 QGROUNDCONTROL PROJECT <http://www.qgroundcontrol.org>
 *
 * QGroundControl is licensed according to the terms in the file
 * COPYING.md in the root of the source code directory.
 *
 ****************************************************************************/

/// @file
///     @author Don Gagne <don@thegagnes.com>

#include "HMILoggingCategory.h"

#include <QSettings>

// Add Global logging categories (not class specific) here using HMI_LOGGING_CATEGORY
HMI_LOGGING_CATEGORY(CanLog, "CanLog")
HMI_LOGGING_CATEGORY(LocalizationLog, "LocalizationLog")
HMI_LOGGING_CATEGORY(VideoManagerLog, "VideoManagerLog")
//HMI_LOGGING_CATEGORY(FirmwareUpgradeVerboseLog, "FirmwareUpgradeVerboseLog")
//HMI_LOGGING_CATEGORY(MissionCommandsLog, "MissionCommandsLog")
//HMI_LOGGING_CATEGORY(MissionItemLog, "MissionItemLog")
//HMI_LOGGING_CATEGORY(ParameterManagerLog, "ParameterManagerLog")
//HMI_LOGGING_CATEGORY(GeotaggingLog, "GeotaggingLog")
//HMI_LOGGING_CATEGORY(RTKGPSLog, "RTKGPSLog")
//HMI_LOGGING_CATEGORY(GuidedActionsControllerLog, "GuidedActionsControllerLog")
//HMI_LOGGING_CATEGORY(ADSBVehicleManagerLog, "ADSBVehicleManagerLog")

HMILoggingCategoryRegister* _instance                                             = nullptr;
const char*                 HMILoggingCategoryRegister::_filterRulesSettingsGroup = "LoggingFilters";

HMILoggingCategoryRegister* HMILoggingCategoryRegister::instance(void)
{
    if (!_instance)
    {
        _instance = new HMILoggingCategoryRegister();
        Q_CHECK_PTR(_instance);
    }

    return _instance;
}

QStringList HMILoggingCategoryRegister::registeredCategories(void)
{
    _registeredCategories.sort();
    return _registeredCategories;
}

void HMILoggingCategoryRegister::setCategoryLoggingOn(const QString& category, bool enable)
{
    QSettings settings;

    settings.beginGroup(_filterRulesSettingsGroup);
    settings.setValue(category, enable);
}

bool HMILoggingCategoryRegister::categoryLoggingOn(const QString& category)
{
    QSettings settings;

    settings.beginGroup(_filterRulesSettingsGroup);
    return settings.value(category, false).toBool();
}

void HMILoggingCategoryRegister::setFilterRulesFromSettings(const QString& commandLineLoggingOptions)
{
    if (!commandLineLoggingOptions.isEmpty())
    {
        _commandLineLoggingOptions = commandLineLoggingOptions;
    }
    QString filterRules;

    filterRules += "*Log.debug=false\n";

    // Set up filters defined in settings
    foreach (QString category, _registeredCategories)
    {
        if (categoryLoggingOn(category))
        {
            filterRules += category;
            filterRules += ".debug=true\n";
        }
    }

    // Command line rules take precedence, so they go last in the list
    if (!_commandLineLoggingOptions.isEmpty())
    {
        QStringList logList = _commandLineLoggingOptions.split(",");

        if (logList[ 0 ] == "full")
        {
            filterRules += "*Log.debug=true\n";
            for (int i = 1; i < logList.count(); i++)
            {
                filterRules += logList[ i ];
                filterRules += ".debug=false\n";
            }
        }
        else
        {
            foreach (const QString& rule, logList)
            {
                filterRules += rule;
                filterRules += ".debug=true\n";
            }
        }
    }

    qDebug() << "Filter rules" << filterRules;
    QLoggingCategory::setFilterRules(filterRules);
}
