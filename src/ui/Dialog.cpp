#include "Dialog.h"
#include "ui_Dialog.h"

#include "XApplication.h"
#include "Toolbox.h"
#include "VehicleManager.h"
#include "FactGroup.h"
#include "Vehicle.h"
#include <QDebug>

Dialog::Dialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::Dialog)
{
    ui->setupUi(this);
    Vehicle * ve = XApp()->toolbox()->vehicleManager()->activeVehicle();

    ///< fact 变化值和ui显示 连接
    connect(ve->carSpeedFact(),&Fact::valueChanged,this,&Dialog::_carUpdated);

    ///< qDebug() << ve->getFact("carSpeed")->type();
}

Dialog::~Dialog()
{
    delete ui;
}

void Dialog::_carUpdated(QVariant value)
{
    ui->label->setText(value.toString());
}

void Dialog::on_pushButton_menu_clicked()
{
    ui->stackedWidget->setCurrentWidget(ui->menu);
}

void Dialog::on_pushButton_system_set_clicked()
{
    ui->stackedWidget->setCurrentWidget(ui->sysSetting);
}

void Dialog::on_pushButton_set2main_clicked()
{
    ui->stackedWidget->setCurrentWidget(ui->main);
}

void Dialog::on_pushButton_mainset_F10_clicked()
{
    ui->stackedWidget->setCurrentWidget(ui->main);
}
