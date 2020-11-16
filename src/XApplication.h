#ifndef XAPPLICATION_H
#define XAPPLICATION_H

#include <QApplication>
#include <QObject>
#include <QElapsedTimer>

class Toolbox;
class QDialog;
class XApplication : public QApplication
{
    Q_OBJECT

public:
    XApplication(int &argc, char* argv[]);
    ~XApplication();

    Toolbox* toolbox(void) {return _toolbox;}

    void _initForAppBoot(); ///< 初始化

    static XApplication*  _app;   ///< 单例，直接被XApp()返回引用。

    uint64_t  msecsSinceBoot(void) { return _msecsElapsedTime.elapsed(); }

private:
    QElapsedTimer       _msecsElapsedTime;

    Toolbox* _toolbox = 0;
    QDialog* dlg = 0;
    QDialog* dlg2 = 0;
};

XApplication* XApp(void);

#endif // XAPPLICATION_H
