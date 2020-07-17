#ifndef XAPPLICATION_H
#define XAPPLICATION_H

#include <QApplication>
#include <QObject>

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

private:
    Toolbox* _toolbox = nullptr;
    QDialog* dlg = nullptr;
    QDialog* dlg2 = nullptr;
};

XApplication* XApp(void);

#endif // XAPPLICATION_H
