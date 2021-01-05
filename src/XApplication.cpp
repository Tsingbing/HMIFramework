#include "XApplication.h"
#include "Dialog2.h"
#include "Fact.h"
#include "FactMetaData.h"
#include "HMIQmlGlobal.h"
#include "Toolbox.h"
#include <QDebug>
#include <QQmlApplicationEngine>
#include <QSettings>

XApplication* XApplication::_app = nullptr;

static QObject* HMIQmlGlobalSingletonFactory(QQmlEngine*, QJSEngine*)
{
    // 我们将此对象创建为Tool，即使它不在toolbox中
    HMIQmlGlobal* qmlGlobal = new HMIQmlGlobal(XApp(), XApp()->toolbox());
    qmlGlobal->setToolbox(XApp()->toolbox());

    return qmlGlobal;
}

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

    _app = nullptr;
}

void XApplication::_initForAppBoot()
{
    _qmlAppEngine = new QQmlApplicationEngine(this);
    _qmlAppEngine->addImportPath("qrc:/qml");
    _qmlAppEngine->load(QUrl(QStringLiteral("qrc:/qml/main.qml")));

    //    dlg = new Dialog2();
    //    Q_CHECK_PTR(dlg);
    //    dlg->show();
}

void XApplication::_initCommon()
{
    static const char* kRefOnly    = "Reference only";
    static const char* kHMIVehicle = "HMI.Vehicle";

    qmlRegisterUncreatableType<Vehicle>(kHMIVehicle, 1, 0, "Vehicle", kRefOnly);

    // 注册 Qml Singletons
    qmlRegisterSingletonType<HMIQmlGlobal>("HMI", 1, 0, "HMI", HMIQmlGlobalSingletonFactory);
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

void XApplication::_shutdown()
{
    delete _qmlAppEngine;
    delete _toolbox;
}

///  返回 XApplication 单例对象.
XApplication* XApp(void)
{
    return XApplication::_app;
}
