/// @file

#include "HMIPalette.h"
#include "XApplication.h"

#include <QApplication>
#include <QPalette>

QList<HMIPalette*> HMIPalette::_paletteObjects;

HMIPalette::Theme HMIPalette::_theme = HMIPalette::Dark;

QMap<int, QMap<int, QMap<QString, QColor>>> HMIPalette::_colorInfoMap;

QStringList HMIPalette::_colors;

HMIPalette::HMIPalette(QObject* parent)
    : QObject(parent)
    , _colorGroupEnabled(true)
{
    if (_colorInfoMap.isEmpty())
    {
        _buildMap();
    }

    // We have to keep track of all HMIPalette objects in the system so we can signal theme change to all of them
    _paletteObjects += this;
}

HMIPalette::~HMIPalette()
{
    bool fSuccess = _paletteObjects.removeOne(this);
    if (!fSuccess)
    {
        qWarning() << "Internal error";
    }
}

void HMIPalette::_buildMap()
{
    //                              Light                 Dark
    //                       Disabled   Enabled    Disabled   Enabled
    DECLARE_HMI_COLOR(window, "#ffffff", "#ffffff", "#222222", "#222222")
    DECLARE_HMI_COLOR(windowShadeLight, "#909090", "#828282", "#707070", "#626262")
    DECLARE_HMI_COLOR(windowShade, "#d9d9d9", "#d9d9d9", "#333333", "#333333")
    DECLARE_HMI_COLOR(windowShadeDark, "#bdbdbd", "#bdbdbd", "#282828", "#282828")
    DECLARE_HMI_COLOR(text, "#9d9d9d", "#000000", "#707070", "#ffffff")
    DECLARE_HMI_COLOR(warningText, "#cc0808", "#cc0808", "#f85761", "#f85761")
    DECLARE_HMI_COLOR(button, "#ffffff", "#ffffff", "#707070", "#626270")
    DECLARE_HMI_COLOR(buttonText, "#9d9d9d", "#000000", "#A6A6A6", "#ffffff")
    DECLARE_HMI_COLOR(buttonHighlight, "#e4e4e4", "#946120", "#3a3a3a", "#fff291")
    DECLARE_HMI_COLOR(buttonHighlightText, "#2c2c2c", "#ffffff", "#2c2c2c", "#000000")
    DECLARE_HMI_COLOR(primaryButton, "#585858", "#8cb3be", "#585858", "#8cb3be")
    DECLARE_HMI_COLOR(primaryButtonText, "#2c2c2c", "#000000", "#2c2c2c", "#000000")
    DECLARE_HMI_COLOR(textField, "#ffffff", "#ffffff", "#707070", "#ffffff")
    DECLARE_HMI_COLOR(textFieldText, "#808080", "#000000", "#000000", "#000000")
    DECLARE_HMI_COLOR(mapButton, "#585858", "#000000", "#585858", "#000000")
    DECLARE_HMI_COLOR(mapButtonHighlight, "#585858", "#be781c", "#585858", "#be781c")
    DECLARE_HMI_COLOR(mapIndicator, "#585858", "#be781c", "#585858", "#be781c")
    DECLARE_HMI_COLOR(mapIndicatorChild, "#585858", "#766043", "#585858", "#766043")
    DECLARE_HMI_COLOR(colorGreen, "#009431", "#009431", "#00e04b", "#00e04b")
    DECLARE_HMI_COLOR(colorOrange, "#b95604", "#b95604", "#de8500", "#de8500")
    DECLARE_HMI_COLOR(colorRed, "#ed3939", "#ed3939", "#f32836", "#f32836")
    DECLARE_HMI_COLOR(colorGrey, "#808080", "#808080", "#bfbfbf", "#bfbfbf")
    DECLARE_HMI_COLOR(colorBlue, "#1a72ff", "#1a72ff", "#536dff", "#536dff")
    DECLARE_HMI_COLOR(alertBackground, "#eecc44", "#eecc44", "#eecc44", "#eecc44")
    DECLARE_HMI_COLOR(alertBorder, "#808080", "#808080", "#808080", "#808080")
    DECLARE_HMI_COLOR(alertText, "#000000", "#000000", "#000000", "#000000")
    DECLARE_HMI_COLOR(missionItemEditor, "#585858", "#dbfef8", "#585858", "#585d83")
    DECLARE_HMI_COLOR(toolStripHoverColor, "#585858", "#9D9D9D", "#585858", "#585d83")
    DECLARE_HMI_COLOR(statusFailedText, "#9d9d9d", "#000000", "#707070", "#ffffff")
    DECLARE_HMI_COLOR(statusPassedText, "#9d9d9d", "#000000", "#707070", "#ffffff")
    DECLARE_HMI_COLOR(statusPendingText, "#9d9d9d", "#000000", "#707070", "#ffffff")
    DECLARE_HMI_COLOR(toolbarBackground, "#ffffff", "#ffffff", "#222222", "#222222")

    // Colors not affecting by theming
    //                                              Disabled    Enabled
    DECLARE_HMI_NONTHEMED_COLOR(brandingPurple, "#4A2C6D", "#4A2C6D")
    DECLARE_HMI_NONTHEMED_COLOR(brandingBlue, "#48D6FF", "#6045c5")
    DECLARE_HMI_NONTHEMED_COLOR(toolStripFGColor, "#707070", "#ffffff")

    // Colors not affecting by theming or enable/disable
    DECLARE_HMI_SINGLE_COLOR(mapWidgetBorderLight, "#ffffff")
    DECLARE_HMI_SINGLE_COLOR(mapWidgetBorderDark, "#000000")
    DECLARE_HMI_SINGLE_COLOR(mapMissionTrajectory, "#be781c")
    DECLARE_HMI_SINGLE_COLOR(surveyPolygonInterior, "green")
    DECLARE_HMI_SINGLE_COLOR(surveyPolygonTerrainCollision, "red")
}

void HMIPalette::setColorGroupEnabled(bool enabled)
{
    _colorGroupEnabled = enabled;
    emit paletteChanged();
}

void HMIPalette::setGlobalTheme(Theme newTheme)
{
    // Mobile build does not have themes
    if (_theme != newTheme)
    {
        _theme = newTheme;
        _signalPaletteChangeToAll();
    }
}

void HMIPalette::_signalPaletteChangeToAll()
{
    // Notify all objects of the new theme
    foreach (HMIPalette* palette, _paletteObjects)
    {
        palette->_signalPaletteChanged();
    }
}

void HMIPalette::_signalPaletteChanged()
{
    emit paletteChanged();
}
