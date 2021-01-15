#ifndef XAPPLICATION_H
#define XAPPLICATION_H

#include <QApplication>
#include <QElapsedTimer>
#include <QMetaMethod>
#include <QMetaObject>
#include <QObject>
#include <QQuickItem>

class QQmlApplicationEngine;
class Toolbox;
class QDialog;

class XApplication : public QApplication
{
    Q_OBJECT

public:
    XApplication(int& argc, char* argv[]);
    ~XApplication();

    static XApplication* _app; ///< 单例，直接被XApp()返回引用。
    Toolbox*             toolbox(void) { return _toolbox; }
    void                 _initForAppBoot(); ///< 初始化
    void                 _initCommon();
    QQuickItem*          mainRootWindow();

    void     setLanguage();
    uint64_t msecsSinceBoot(void) { return _msecsElapsedTime.elapsed(); }

    /// Shutdown the application object
    void _shutdown();

private:
    QObject* _rootQmlObject();

private:
    QElapsedTimer _msecsElapsedTime;
    Toolbox*      _toolbox        = nullptr;
    QQuickItem*   _mainRootWindow = nullptr;
    QDialog*      dlg             = nullptr;

    QQmlApplicationEngine* _qmlAppEngine = nullptr;

    QLocale _locale;
};

XApplication* XApp(void);

#endif // XAPPLICATION_H
