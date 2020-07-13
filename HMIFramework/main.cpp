#include "Dialog.h"

#include <QApplication>
#include <XApplication.h>

int main(int argc, char *argv[])
{
    XApplication a(argc, argv);
    Dialog w;
    w.show();
    return a.exec();
}
