#include "XApplication.h"
#include "AppMessages.h"
#include "Dialog2.h"
#include "Fact.h"
#include "FactMetaData.h"
#include "HMIPalette.h"
#include "HMIQmlGlobal.h"
#include "ScreenToolsController.h"
#include "Toolbox.h"
#include <QDebug>
#include <QLibraryInfo>
#include <QQmlApplicationEngine>
#include <QQmlContext>
#include <QSettings>

XApplication* XApplication::_app = nullptr;

// Qml Singleton factories

static QObject* screenToolsControllerSingletonFactory(QQmlEngine*, QJSEngine*)
{
    ScreenToolsController* screenToolsController = new ScreenToolsController;
    return screenToolsController;
}

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
    this->setApplicationVersion(QString(GIT_VERSION));

    // 设置 settings 格式
    QSettings::setDefaultFormat(QSettings::IniFormat);
    QSettings settings;
    qDebug() << "Settings location" << settings.fileName() << "Is writable?:" << settings.isWritable();

    _toolbox = new Toolbox(this);
    _toolbox->setChildToolboxes();

    setLanguage();
}

XApplication::~XApplication()
{
    if (dlg)
    {
        delete dlg;
    }

    _app = nullptr;
}

void XApplication::showMessage(const QString& message)
{
    // PreArm messages are handled by Vehicle and shown in Map
    if (message.startsWith(QStringLiteral("PreArm")) || message.startsWith(QStringLiteral("preflight"), Qt::CaseInsensitive))
    {
        return;
    }
    QObject* rootQmlObject = _rootQmlObject();
    if (rootQmlObject)
    {
        QVariant varReturn;
        QVariant varMessage = QVariant::fromValue(message);
        QMetaObject::invokeMethod(_rootQmlObject(), "showMessage", Q_RETURN_ARG(QVariant, varReturn), Q_ARG(QVariant, varMessage));
    }
    else
    {
        qWarning() << "Internal error";
    }
}

void XApplication::_initForAppBoot()
{
    //QQuick UI 界面显示
    _qmlAppEngine = new QQmlApplicationEngine(this);
    _qmlAppEngine->addImportPath("qrc:/qml");
    _qmlAppEngine->rootContext()->setContextProperty("debugMessageModel", AppMessages::getModel());
    _qmlAppEngine->load(QUrl(QStringLiteral("qrc:/qml/MainRootWindow1.qml")));
    //QWidget UI 界面显示
    //    dlg = new Dialog2();
    //    Q_CHECK_PTR(dlg);
    //    dlg->show();
}

void XApplication::_initCommon()
{
    static const char* kRefOnly    = "Reference only";
    static const char* kHMIVehicle = "HMI.Vehicle";

    qmlRegisterType<HMIPalette>("HMI.Palette", 1, 0, "HMIPalette");

    qmlRegisterUncreatableType<Vehicle>(kHMIVehicle, 1, 0, "Vehicle", kRefOnly);
    //qmlRegisterUncreatableType<SettingsManager>("HMI.SettingsManager", 1, 0, "SettingsManager", "Reference only");
    // 注册 Qml Singletons
    qmlRegisterSingletonType<HMIQmlGlobal>("HMI", 1, 0, "HMI", HMIQmlGlobalSingletonFactory);
    qmlRegisterSingletonType<ScreenToolsController>("HMI.ScreenToolsController", 1, 0, "ScreenToolsController", screenToolsControllerSingletonFactory);
}

QQuickItem* XApplication::mainRootWindow()
{
    if (!_mainRootWindow)
    {
        _mainRootWindow = reinterpret_cast<QQuickItem*>(_rootQmlObject());
    }
    return _mainRootWindow;
}

void XApplication::setLanguage()
{
    _locale = QLocale::system();
    qDebug() << "System reported locale:" << _locale << _locale.name();
    int langID = toolbox()->settingsManager()->appSettings()->language()->rawValue().toInt();

    //-- See App.SettinsGroup.json for index
    if (langID)
    {
        switch (langID)
        {
            case 1:
                _locale = QLocale(QLocale::Chinese);
                break;
            case 2:
                _locale = QLocale(QLocale::English);
                break;
        }
    }

    qCDebug(LocalizationLog) << "Loading localizations for" << _locale.name();
    _app->removeTranslator(&_qgcTranslatorJSON);
    _app->removeTranslator(&_qgcTranslatorSourceCode);
    _app->removeTranslator(&_qgcTranslatorQtLibs);
    if (_locale.name() != "en_US")
    {
        QLocale::setDefault(_locale);
        //        if (_qgcTranslatorQtLibs.load("qt_" + _locale.name(), QLibraryInfo::location(QLibraryInfo::TranslationsPath)))
        //        {
        //            _app->installTranslator(&_qgcTranslatorQtLibs);
        //        }
        //        else
        //        {
        //            qCWarning(LocalizationLog) << "Qt lib localization for" << _locale.name() << "is not present";
        //        }
        if (_qgcTranslatorSourceCode.load(_locale, QLatin1String("qgc_source_"), "", ":/i18n"))
        {
            _app->installTranslator(&_qgcTranslatorSourceCode);
        }
        else
        {
            qCWarning(LocalizationLog) << "Error loading source localization for" << _locale.name();
        }
        if (_qgcTranslatorJSON.load(_locale, QLatin1String("qgc_json_"), "", ":/i18n"))
        {
            _app->installTranslator(&_qgcTranslatorJSON);
        }
        else
        {
            qCWarning(LocalizationLog) << "Error loading json localization for" << _locale.name();
        }
    }

    //    qDebug() << "Loading localization for" << _locale.name();
    //    _app->removeTranslator(&_QGCTranslator);
    //    _app->removeTranslator(&_QGCTranslatorQt);
    //    _app->removeTranslator(&_QGCTranslatorJson);
    //    if (_QGCTranslatorQt.load("qt_" + _locale.name(), QLibraryInfo::location(QLibraryInfo::TranslationsPath)))
    //    {
    //        _app->installTranslator(&_QGCTranslatorQt);
    //    }
    //    else
    //    {
    //        qDebug() << "Qt localization for" << _locale.name() << "is not present";
    //    }

    //    if (_QGCTranslator.load(_locale, QLatin1String("qgc_"), "", ":/i18n"))
    //    {
    //        QLocale::setDefault(_locale);
    //        _app->installTranslator(&_QGCTranslator);
    //    }
    //    else
    //    {
    //        qDebug() << "Error loading application localization for" << _locale.name();
    //    }

    //    if (_QGCTranslatorJson.load(_locale, QLatin1String("qgc-json_"), "", ":/i18n"))
    //    {
    //        QLocale::setDefault(_locale);
    //        _app->installTranslator(&_QGCTranslatorJson);
    //    }
    //    else
    //    {
    //        qDebug() << "Error loading application localization for" << _locale.name();
    //    }

    if (_qmlAppEngine)
        _qmlAppEngine->retranslate();
    emit languageChanged(_locale);
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
