#include "XApplication.h"
#include "Dialog2.h"
#include "Toolbox.h"
#include <QDebug>
#include <QQmlApplicationEngine>
#include <QSettings>

XApplication* XApplication::_app = nullptr;

XApplication::XApplication(int& argc, char* argv[])
    : QApplication(argc, argv)
{
    _app = this;
    // _msecsElapsedTime.start();

    setApplicationName(APPLICATION_NAME);
    setOrganizationName(ORG_NAME);
    setApplicationVersion(QString(GIT_VERSION));

    // 设置 settings 格式
    QSettings::setDefaultFormat(QSettings::IniFormat);
    QSettings settings;
    qDebug() << "Settings location" << settings.fileName() << "Is writable?:" << settings.isWritable();

    _toolbox = new Toolbox(this);
    _toolbox->setChildToolboxes();
}

XApplication::~XApplication()
{
    if (dlg)
    {
        delete dlg;
    }
    delete _toolbox;
    _app = nullptr;
}

void XApplication::_initForAppBoot()
{
    _qmlAppEngine = new QQmlApplicationEngine(this);
    _qmlAppEngine->addImportPath("qrc:/qml");
    _qmlAppEngine->load(QUrl(QStringLiteral("qrc:/qml/ui/main.qml")));

    //    dlg = new Dialog2();
    //    Q_CHECK_PTR(dlg);
    //    dlg->show();
    //qDebug() << "timestamp = " << msecsSinceBoot();
    //    dlg2 = new Dialog2();
    //    Q_CHECK_PTR(dlg2);
    //    dlg2->show();
    //qDebug() << "timestamp = " << msecsSinceBoot();
}

QQuickItem* XApplication::mainRootWindow()
{
    if (!_mainRootWindow)
    {
        _mainRootWindow = reinterpret_cast<QQuickItem*>(_rootQmlObject());
    }
    return _mainRootWindow;
}

QObject* XApplication::_rootQmlObject()
{
    if (_qmlAppEngine && _qmlAppEngine->rootObjects().size())
        return _qmlAppEngine->rootObjects()[ 0 ];
    return nullptr;
}

///  返回 XApplication 单例对象.
XApplication* XApp(void)
{
    return XApplication::_app;
}
