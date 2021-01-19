#ifndef XAPPLICATION_H
#define XAPPLICATION_H

#include "HMILoggingCategory.h"
#include <QApplication>
#include <QElapsedTimer>
#include <QMetaMethod>
#include <QMetaObject>
#include <QObject>
#include <QQuickItem>
#include <QTranslator>

class QQmlApplicationEngine;
class Toolbox;
class QDialog;

class XApplication : public QApplication
{
    Q_OBJECT

public:
    XApplication(int& argc, char* argv[]);
    ~XApplication();

    /// Show a non-modal message to the user
    void showMessage(const QString& message);

    static XApplication* _app; ///< 单例，直接被XApp()返回引用。
    Toolbox*             toolbox(void) { return _toolbox; }
    void                 _initForAppBoot(); ///< 初始化
    void                 _initCommon();
    QQuickItem*          mainRootWindow();

    void     setLanguage();
    uint64_t msecsSinceBoot(void) { return _msecsElapsedTime.elapsed(); }

    /// @brief Returns true if Qt debug output should be logged to a file
    bool logOutput(void) { return _logOutput; }

    /// Shutdown the application object
    void _shutdown();

signals:
    void languageChanged(const QLocale locale);

private:
    QObject* _rootQmlObject();

private:
    QElapsedTimer _msecsElapsedTime;
    Toolbox*      _toolbox        = nullptr;
    QQuickItem*   _mainRootWindow = nullptr;
    QDialog*      dlg             = nullptr;

    QQmlApplicationEngine* _qmlAppEngine = nullptr;
    bool                   _logOutput    = false; ///< true: Log Qt debug output to file
    QLocale                _locale;

    QTranslator _QGCTranslator;
    QTranslator _QGCTranslatorQt;
    QTranslator _QGCTranslatorJson;

    QTranslator _qgcTranslatorSourceCode; ///< translations for source code C++/Qml
    QTranslator _qgcTranslatorJSON;       ///< translations for json files
    QTranslator _qgcTranslatorQtLibs;     ///< tranlsations for Qt libraries
};

XApplication* XApp(void);

#endif // XAPPLICATION_H
