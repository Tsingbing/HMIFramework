#ifndef XAPPLICATION_H
#define XAPPLICATION_H

#include <QApplication>
#include <QObject>

class Toolbox;

class XApplication : public QApplication
{
    Q_OBJECT

public:
    XApplication(int &argc, char* argv[]);
    ~XApplication();

    Toolbox* toolbox(void) {return _toolbox;}

private:
    Toolbox* _toolbox = nullptr;
};

#endif // XAPPLICATION_H
