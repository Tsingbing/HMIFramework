/// @file

#include "ScreenToolsController.h"
#include <QFontDatabase>
#include <QFontMetrics>
#include <QScreen>

#include "SettingsManager.h"

ScreenToolsController::ScreenToolsController()
{
}

bool ScreenToolsController::hasTouch() const
{
    return QTouchDevice::devices().count() > 0 || isMobile();
}

QString ScreenToolsController::fixedFontFamily() const
{
    return QFontDatabase::systemFont(QFontDatabase::FixedFont).family();
}

QString ScreenToolsController::normalFontFamily() const
{
    //-- See App.SettinsGroup.json for index
    int langID = XApp()->toolbox()->settingsManager()->appSettings()->language()->rawValue().toInt();
    if (langID == 6 /*Korean*/)
    {
        return QString("fonts/NanumGothic-Regular");
    }
    else
    {
        return QString("opensans");
    }
}

QString ScreenToolsController::boldFontFamily() const
{
    //-- See App.SettinsGroup.json for index
    int langID = XApp()->toolbox()->settingsManager()->appSettings()->language()->rawValue().toInt();
    if (langID == 6 /*Korean*/)
    {
        return QString("NanumGothic-Bold");
    }
    else
    {
        return QString("opensans-demibold");
    }
}

double ScreenToolsController::defaultFontDescent(int pointSize) const
{
    return QFontMetrics(QFont(normalFontFamily(), pointSize)).descent();
}
