#ifndef HMIPalette_h
#define HMIPalette_h

#include <QColor>
#include <QMap>
#include <QObject>

#define DECLARE_HMI_COLOR(name, lightDisabled, lightEnabled, darkDisabled, darkEnabled)                                   \
    {                                                                                                                     \
        PaletteColorInfo_t colorInfo = {                                                                                  \
            {QColor(lightDisabled), QColor(lightEnabled)},                                                                \
            {QColor(darkDisabled), QColor(darkEnabled)}};                                                                 \
        _colorInfoMap[ Light ][ ColorGroupEnabled ][ QStringLiteral(#name) ]  = colorInfo[ Light ][ ColorGroupEnabled ];  \
        _colorInfoMap[ Light ][ ColorGroupDisabled ][ QStringLiteral(#name) ] = colorInfo[ Light ][ ColorGroupDisabled ]; \
        _colorInfoMap[ Dark ][ ColorGroupEnabled ][ QStringLiteral(#name) ]   = colorInfo[ Dark ][ ColorGroupEnabled ];   \
        _colorInfoMap[ Dark ][ ColorGroupDisabled ][ QStringLiteral(#name) ]  = colorInfo[ Dark ][ ColorGroupDisabled ];  \
        _colors << #name;                                                                                                 \
    }

#define DECLARE_HMI_NONTHEMED_COLOR(name, disabledColor, enabledColor)                                                    \
    {                                                                                                                     \
        PaletteColorInfo_t colorInfo = {                                                                                  \
            {QColor(disabledColor), QColor(enabledColor)},                                                                \
            {QColor(disabledColor), QColor(enabledColor)}};                                                               \
        _colorInfoMap[ Light ][ ColorGroupEnabled ][ QStringLiteral(#name) ]  = colorInfo[ Light ][ ColorGroupEnabled ];  \
        _colorInfoMap[ Light ][ ColorGroupDisabled ][ QStringLiteral(#name) ] = colorInfo[ Light ][ ColorGroupDisabled ]; \
        _colorInfoMap[ Dark ][ ColorGroupEnabled ][ QStringLiteral(#name) ]   = colorInfo[ Dark ][ ColorGroupEnabled ];   \
        _colorInfoMap[ Dark ][ ColorGroupDisabled ][ QStringLiteral(#name) ]  = colorInfo[ Dark ][ ColorGroupDisabled ];  \
        _colors << #name;                                                                                                 \
    }

#define DECLARE_HMI_SINGLE_COLOR(name, color)                                                                             \
    {                                                                                                                     \
        PaletteColorInfo_t colorInfo = {                                                                                  \
            {QColor(color), QColor(color)},                                                                               \
            {QColor(color), QColor(color)}};                                                                              \
        _colorInfoMap[ Light ][ ColorGroupEnabled ][ QStringLiteral(#name) ]  = colorInfo[ Light ][ ColorGroupEnabled ];  \
        _colorInfoMap[ Light ][ ColorGroupDisabled ][ QStringLiteral(#name) ] = colorInfo[ Light ][ ColorGroupDisabled ]; \
        _colorInfoMap[ Dark ][ ColorGroupEnabled ][ QStringLiteral(#name) ]   = colorInfo[ Dark ][ ColorGroupEnabled ];   \
        _colorInfoMap[ Dark ][ ColorGroupDisabled ][ QStringLiteral(#name) ]  = colorInfo[ Dark ][ ColorGroupDisabled ];  \
        _colors << #name;                                                                                                 \
    }

#define DEFINE_HMI_COLOR(NAME, SETNAME)                                                                                                                  \
    Q_PROPERTY(QColor NAME READ NAME WRITE SETNAME NOTIFY paletteChanged)                                                                                \
    Q_PROPERTY(QStringList NAME##Colors READ NAME##Colors NOTIFY paletteChanged)                                                                         \
    QColor      NAME() const { return _colorInfoMap[ _theme ][ _colorGroupEnabled ? ColorGroupEnabled : ColorGroupDisabled ][ QStringLiteral(#NAME) ]; } \
    QStringList NAME##Colors() const                                                                                                                     \
    {                                                                                                                                                    \
        QStringList c;                                                                                                                                   \
        c << _colorInfoMap[ Light ][ ColorGroupEnabled ][ QStringLiteral(#NAME) ].name(QColor::HexRgb);                                                  \
        c << _colorInfoMap[ Light ][ ColorGroupDisabled ][ QStringLiteral(#NAME) ].name(QColor::HexRgb);                                                 \
        c << _colorInfoMap[ Dark ][ ColorGroupEnabled ][ QStringLiteral(#NAME) ].name(QColor::HexRgb);                                                   \
        c << _colorInfoMap[ Dark ][ ColorGroupDisabled ][ QStringLiteral(#NAME) ].name(QColor::HexRgb);                                                  \
        return c;                                                                                                                                        \
    }                                                                                                                                                    \
    void SETNAME(const QColor& color)                                                                                                                    \
    {                                                                                                                                                    \
        _colorInfoMap[ _theme ][ _colorGroupEnabled ? ColorGroupEnabled : ColorGroupDisabled ][ QStringLiteral(#NAME) ] = color;                         \
        _signalPaletteChangeToAll();                                                                                                                     \
    }

/*!
 HMIPalette is used in QML ui to expose color properties for the QGC palette. There are two
 separate palettes in QGC, light and dark. The light palette is for outdoor use and the dark
 palette is for indoor use. Each palette also has a set of different colors for enabled and
 disabled states.

 Usage:

        import HMI.Palette 1.0

        Rectangle {
            anchors.fill:   parent
            color:          hmiPal.window

            HMIPalette { id: hmiPal: colorGroupEnabled: enabled }
        }
*/

class HMIPalette : public QObject
{
    Q_OBJECT

public:
    enum ColorGroup
    {
        ColorGroupDisabled = 0,
        ColorGroupEnabled,
        cMaxColorGroup
    };

    enum Theme
    {
        Light = 0,
        Dark,
        cMaxTheme
    };
    Q_ENUM(Theme)

    typedef QColor PaletteColorInfo_t[ cMaxTheme ][ cMaxColorGroup ];

    Q_PROPERTY(Theme globalTheme READ globalTheme WRITE setGlobalTheme NOTIFY paletteChanged)
    Q_PROPERTY(bool colorGroupEnabled READ colorGroupEnabled WRITE setColorGroupEnabled NOTIFY paletteChanged)
    Q_PROPERTY(QStringList colors READ colors CONSTANT)

    DEFINE_HMI_COLOR(window, setWindow)
    DEFINE_HMI_COLOR(windowShadeLight, setWindowShadeLight)
    DEFINE_HMI_COLOR(windowShade, setWindowShade)
    DEFINE_HMI_COLOR(windowShadeDark, setWindowShadeDark)
    DEFINE_HMI_COLOR(text, setText)
    DEFINE_HMI_COLOR(warningText, setWarningText)
    DEFINE_HMI_COLOR(button, setButton)
    DEFINE_HMI_COLOR(buttonText, setButtonText)
    DEFINE_HMI_COLOR(buttonHighlight, setButtonHighlight)
    DEFINE_HMI_COLOR(buttonHighlightText, setButtonHighlightText)
    DEFINE_HMI_COLOR(primaryButton, setPrimaryButton)
    DEFINE_HMI_COLOR(primaryButtonText, setPrimaryButtonText)
    DEFINE_HMI_COLOR(textField, setTextField)
    DEFINE_HMI_COLOR(textFieldText, setTextFieldText)
    DEFINE_HMI_COLOR(mapButton, setMapButton)
    DEFINE_HMI_COLOR(mapButtonHighlight, setMapButtonHighlight)
    DEFINE_HMI_COLOR(mapIndicator, setMapIndicator)
    DEFINE_HMI_COLOR(mapIndicatorChild, setMapIndicatorChild)
    DEFINE_HMI_COLOR(mapWidgetBorderLight, setMapWidgetBorderLight)
    DEFINE_HMI_COLOR(mapWidgetBorderDark, setMapWidgetBorderDark)
    DEFINE_HMI_COLOR(mapMissionTrajectory, setMapMissionTrajectory)
    DEFINE_HMI_COLOR(brandingPurple, setBrandingPurple)
    DEFINE_HMI_COLOR(brandingBlue, setBrandingBlue)
    DEFINE_HMI_COLOR(colorGreen, setColorGreen)
    DEFINE_HMI_COLOR(colorOrange, setColorOrange)
    DEFINE_HMI_COLOR(colorRed, setColorRed)
    DEFINE_HMI_COLOR(colorGrey, setColorGrey)
    DEFINE_HMI_COLOR(colorBlue, setColorBlue)
    DEFINE_HMI_COLOR(alertBackground, setAlertBackground)
    DEFINE_HMI_COLOR(alertBorder, setAlertBorder)
    DEFINE_HMI_COLOR(alertText, setAlertText)
    DEFINE_HMI_COLOR(missionItemEditor, setMissionItemEditor)
    DEFINE_HMI_COLOR(statusFailedText, setstatusFailedText)
    DEFINE_HMI_COLOR(statusPassedText, setstatusPassedText)
    DEFINE_HMI_COLOR(statusPendingText, setstatusPendingText)
    DEFINE_HMI_COLOR(surveyPolygonInterior, setSurveyPolygonInterior)
    DEFINE_HMI_COLOR(surveyPolygonTerrainCollision, setSurveyPolygonTerrainCollision)
    DEFINE_HMI_COLOR(toolbarBackground, setToolbarBackground)
    DEFINE_HMI_COLOR(toolStripFGColor, setToolStripFGColor)
    DEFINE_HMI_COLOR(toolStripHoverColor, setToolStripHoverColor)

    HMIPalette(QObject* parent = nullptr);
    ~HMIPalette();

    QStringList colors() const { return _colors; }
    bool        colorGroupEnabled() const { return _colorGroupEnabled; }
    void        setColorGroupEnabled(bool enabled);

    static Theme globalTheme() { return _theme; }
    static void  setGlobalTheme(Theme newTheme);

signals:
    void paletteChanged();

private:
    static void _buildMap();
    static void _signalPaletteChangeToAll();
    void        _signalPaletteChanged();
    void        _themeChanged();

    static Theme       _theme;             ///< There is a single theme for all palettes
    bool               _colorGroupEnabled; ///< Currently selected ColorGroup. true: enabled, false: disabled
    static QStringList _colors;

    static QMap<int, QMap<int, QMap<QString, QColor>>> _colorInfoMap;   // theme -> colorGroup -> color name -> color
    static QList<HMIPalette*>                          _paletteObjects; ///< List of all active HMIPalette objects
};

#endif
