#include "XApplication.h"
#include "Toolbox.h"

#include "Dialog.h"
#include "Dialog2.h"


XApplication* XApplication::_app = nullptr;

XApplication::XApplication(int &argc, char *argv[])
    : QApplication (argc, argv)
{
    _app = this;
    _toolbox = new Toolbox(this);
    _toolbox->setChildToolboxes();

}

XApplication::~XApplication()
{
    if (dlg) {
       delete dlg;
    }
    delete _toolbox;
    _app = nullptr;
}

void XApplication::_initForAppBoot()
{
    dlg = new Dialog();
    Q_CHECK_PTR(dlg);
    dlg->show();

    dlg2 = new Dialog2();
    Q_CHECK_PTR(dlg2);
    dlg2->show();
}

/// @brief Returns the XApplication object singleton.
XApplication* XApp(void)
{
    return XApplication::_app;
}
