#include <QApplication>
#include <QDebug>
#include <XApplication.h>

int main(int argc, char* argv[])
{
    qputenv("QT_IM_MODULE", QByteArray("qtvirtualkeyboard"));
    XApplication* app = new XApplication(argc, argv);
    Q_CHECK_PTR(app);

    app->_initCommon();
    app->_initForAppBoot();

    int exitCode = app->exec();
    app->_shutdown();
    delete app;

    qDebug() << "After app delete";
    return exitCode;
}
