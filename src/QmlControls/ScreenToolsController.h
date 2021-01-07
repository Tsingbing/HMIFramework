/****************************************************************************
 *
 * (c) 2020-2021 HMI PROJECT <http://www.hmi.org>
 *
 * HMI is licensed according to the terms in the file
 * COPYING.md in the root of the source code directory.
 *
 ****************************************************************************/

/// @file

#ifndef ScreenToolsController_H
#define ScreenToolsController_H

#include "XApplication.h"
#include <QCursor>
#include <QQuickItem>

/*!
    @brief Screen helper tools for QML widgets
*/

/// This Qml control is used to return screen parameters
class ScreenToolsController : public QQuickItem
{
    Q_OBJECT
public:
    ScreenToolsController();
    Q_PROPERTY(bool isMobile READ isMobile CONSTANT)
    Q_PROPERTY(bool isLinux READ isLinux CONSTANT)
    Q_PROPERTY(bool hasTouch READ hasTouch CONSTANT)
    Q_PROPERTY(QString fixedFontFamily READ fixedFontFamily CONSTANT)
    Q_PROPERTY(QString normalFontFamily READ normalFontFamily CONSTANT)
    Q_PROPERTY(QString boldFontFamily READ boldFontFamily CONSTANT)

    // Returns current mouse position
    Q_INVOKABLE int mouseX(void) { return QCursor::pos().x(); }
    Q_INVOKABLE int mouseY(void) { return QCursor::pos().y(); }

    // QFontMetrics::descent for default font
    Q_INVOKABLE double defaultFontDescent(int pointSize) const;

    bool isMobile() const
    {
        //return XApp()->fakeMobile();
        return true;
    }

#if defined(Q_OS_LINUX)

    bool isLinux()
    {
        return true;
    }
#endif
    bool    hasTouch() const;
    QString fixedFontFamily() const;
    QString normalFontFamily() const;
    QString boldFontFamily() const;
};
#endif
