#include "XApplication.h"
#include "Toolbox.h"

XApplication::XApplication(int &argc, char *argv[])
    : QApplication (argc, argv)
{
    _toolbox = new Toolbox(this);
    //_toolbox->setChildToolboxes();
}

XApplication::~XApplication()
{
    delete _toolbox;
}
