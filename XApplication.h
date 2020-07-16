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

    void _initForAppBoot();

    static XApplication*  _app;   ///< Our own singleton. Should be reference directly by qgcApp

private:
    Toolbox* _toolbox = nullptr;
    QDialog* dlg = nullptr;
};


XApplication* XApp(void);

#endif // XAPPLICATION_H
