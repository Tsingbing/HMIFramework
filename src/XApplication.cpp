﻿#include "XApplication.h"
#include "Toolbox.h"
#include <QSettings>
#include "Dialog.h"
#include "Dialog2.h"
#include <QDebug>

XApplication* XApplication::_app = nullptr;

XApplication::XApplication(int &argc, char *argv[])
    : QApplication (argc, argv)
{
    _app = this;
   // _msecsElapsedTime.start();

//    setApplicationName(APPLICATION_NAME);
//    setOrganizationName(ORG_NAME);
//    setApplicationVersion(QString(GIT_VERSION));

    // Set settings format
    //QSettings::setDefaultFormat(QSettings::IniFormat);
    //QSettings settings;
    //qDebug() << "Settings location" << settings.fileName() << "Is writable?:" << settings.isWritable();

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
    //qDebug() << "timestamp = " << msecsSinceBoot();
    dlg2 = new Dialog2();
    Q_CHECK_PTR(dlg2);
    dlg2->show();
    //qDebug() << "timestamp = " << msecsSinceBoot();
}

/// @brief Returns the XApplication object singleton.
XApplication* XApp(void)
{
    return XApplication::_app;
}
