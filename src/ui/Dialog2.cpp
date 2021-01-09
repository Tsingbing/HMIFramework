#include "Dialog2.h"
#include "ui_Dialog2.h"

#include "FactGroup.h"
#include "SettingsManager.h"
#include "Toolbox.h"
#include "Vehicle.h"
#include "VehicleManager.h"
#include "XApplication.h"
#include <QDebug>

Dialog2::Dialog2(QWidget* parent)
    : QDialog(parent)
    , ui(new Ui::Dialog2)
{
    ui->setupUi(this);
    ve = XApp()->toolbox()->vehicleManager()->activeVehicle();
    cl = XApp()->toolbox()->linkManager()->canlink();
    sm = XApp()->toolbox()->settingsManager();
    ///< fact 变化值和ui显示 连接
    connect(ve->supplyVoltageFact(), &Fact::valueChanged, [=](QVariant value) { ui->label_dianya->setText(ve->supplyVoltageFact()->cookedValueString()); });
    //ui->lineEdit->setText(sm->appSettings()->language()->cookedValue().toString());
    //sm->appSettings()->language()->setRawValue(100);
    //sm->appSettings()->appFontPointSize()->setRawValue(15);
}

Dialog2::~Dialog2()
{
    delete ui;
}

void Dialog2::on_pushButton_menu_F4_clicked()
{
    ui->stackedWidget->setCurrentWidget(ui->main);
}

void Dialog2::on_pushButton_menu_F5_clicked()
{
    ui->stackedWidget->setCurrentWidget(ui->page_2);
}

void Dialog2::on_pushButton_menu_F4_2_clicked()
{
    ui->stackedWidget->setCurrentWidget(ui->main);
}

void Dialog2::on_pushButton_menu_F5_2_clicked()
{
    ui->stackedWidget->setCurrentWidget(ui->page_2);
}

void Dialog2::on_pushButton_frontLight_clicked()
{
    static bool b = false;
    b             = !b;
    ve->sendFrontLightSwitch(b);
}

void Dialog2::on_pushButton_backLight_clicked()
{
    static bool b = false;
    b             = !b;
    ve->sendBackLightSwitch(b);
}

void Dialog2::on_pushButton_alarmLight_clicked()
{
    static bool b = false;
    b             = !b;
    ve->sendAlarmSwitch(b);
}

void Dialog2::on_pushButton_pochaiduan_clicked()
{
    static bool b = false;
    b             = !b;
    ve->sendPoChaiLockSwitch(b);
}

void Dialog2::on_pushButton_wajueduan_clicked()
{
    static bool b = false;
    b             = !b;
    ve->sendWajueLockSwitch(b);
}

void Dialog2::on_pushButton_pochaiduanquick_clicked()
{
    static bool b = false;
    b             = !b;
    ve->sendPoChaiQuickSwitch(b);
}

void Dialog2::on_lineEdit_returnPressed()
{
}

void Dialog2::on_lineEdit_editingFinished()
{
}

void Dialog2::on_lineEdit_textChanged(const QString& arg1)
{
    sm->appSettings()->language()->setRawValue(ui->lineEdit->text());
}
