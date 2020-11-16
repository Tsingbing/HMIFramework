﻿#include <QApplication>
#include <XApplication.h>
#include <QDebug>

int main(int argc, char *argv[])
{
    XApplication *app = new XApplication(argc, argv);
    Q_CHECK_PTR(app);

    app->_initForAppBoot();

    int exitCode = app->exec();

    delete app;

    qDebug() << "After app delete";
    return exitCode;
}
